/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:20:03 by aprevrha          #+#    #+#             */
/*   Updated: 2023/11/07 16:23:24 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_paused;

void	handle_sigusr(int signum, awd)
{
	if (CLIENT_USLEEP)
		usleep(CLIENT_USLEEP);
	if (signum == SIGUSR1)
		g_paused = 0;
	else if (signum == SIGUSR2)
	{
		write(1, "\033[32mMessage was recived!\033[0m\n", 30);
		exit(0);
	}
}

int	send_bit(int bit, unsigned int pid)
{
	if (bit == 0)
		return (kill(pid, SIGUSR1));
	else if (bit == 1)
		return (kill(pid, SIGUSR2));
	return (-1);
}

void	send_byte(char byte, unsigned int pid)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_paused = 1;
		send_bit((byte >> bit) & 0x1, pid);
		while (g_paused)
			pause();
		bit--;
	}
}

int	send_msg(char *msg, __pid_t server_pid)
{
	int	i;

	i = 0;
	g_paused = 1;
	while (g_paused)
	{
		if (server_pid == 0 || send_bit(0x0, server_pid) == -1)
			return (
				ft_printf("\033[41mError:\033[0m Can't reach server.\n"), 1);
		if (i > 0)
			sleep(1);
		if (i > CLIENT_TIMEOUT)
			return (ft_printf("\033[41mError:\033[0m Timeout.\n"), 1);
		i++;
	}
	i = 0;
	while (msg[i])
	{
		send_byte(msg[i], server_pid);
		i++;
	}
	send_byte(0x0, server_pid);
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigusr;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
	{
		ft_printf("%s: usage: %s <server_pid> <message>\n", argv[0], argv[0]);
		return (1);
	}
	return (send_msg(argv[2], ft_atoi(argv[1])));
}
