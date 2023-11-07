/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:18:28 by aprevrha          #+#    #+#             */
/*   Updated: 2023/11/07 15:43:03 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	handle_byte(unsigned char byte, __pid_t sender_pid)
{
	if (byte == 0)
	{
		write(1, "\n", 1);
		kill(sender_pid, SIGUSR2);
		return (1);
	}
	write(1, &byte, 1);
	return (0);
}

void	handle_sigusr(int signum, siginfo_t *info, void *context)
{
	static __pid_t			client_pid = -1;
	static int				bit = 8;
	static unsigned char	byte = 0;

	if (info->si_pid != client_pid && client_pid != -1)
		return ;
	else if (client_pid == -1)
	{
		client_pid = info->si_pid;
		kill(client_pid, SIGUSR1);
		return ;
	}
	(void)context;
	byte = byte << 1;
	if (signum == SIGUSR2)
		byte = byte | 0x1;
	bit--;
	if (bit <= 0)
	{
		if (handle_byte(byte, info->si_pid))
			client_pid = -1;
		byte = 0x0;
		bit = 8;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %i\n", getpid());
	sa.sa_handler = NULL;
	sa.sa_sigaction = &handle_sigusr;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		sleep(1);
	}
}
