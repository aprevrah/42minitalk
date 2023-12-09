/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:20:03 by aprevrha          #+#    #+#             */
/*   Updated: 2023/12/09 21:08:31 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_info	g_info;

int	send_bit(int bit, unsigned int pid)
{
	if (bit == 0)
		return (kill(pid, SIGUSR1));
	else if (bit == 1)
		return (kill(pid, SIGUSR2));
	return (-1);
}

void	handle_sigusr(int signum)
{
	static int			bit = 7;
	static unsigned int	byte = 0;

	g_info.response = 1;
	if (signum == SIGUSR2)
	{
		write(1, "\033[32mMessage was recived!\033[0m\n", 30);
		exit(0);
	}
	send_bit((g_info.msg[byte] >> bit) & 0x1, g_info.pid);
	bit--;
	if (bit < 0)
	{
		bit = 7;
		byte++;
	}
}

int	connect(void)
{
	int	s;

	s = 0;
	while (g_info.response == 0)
	{
		if (g_info.pid == 0 || send_bit(0x0, g_info.pid) == -1)
			return (
				ft_printf("\033[41mError:\033[0m Can't reach server.\n"), 1);
		if (s >= CLIENT_TIMEOUT)
			return (ft_printf("\033[41mError:\033[0m Timeout.\n"), 1);
		sleep(1);
		s++;
	}
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
	g_info.msg = argv[2];
	g_info.pid = ft_atoi(argv[1]);
	g_info.response = 0;
	if (connect() == 1)
		return (1);
	while (1)
		pause();
	return (0);
}
