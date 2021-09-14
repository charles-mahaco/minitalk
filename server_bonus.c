/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:47:11 by charles           #+#    #+#             */
/*   Updated: 2021/08/31 16:47:14 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sig_handler(int sig, siginfo_t *siginfo, void *oldact)
{
	static char		c = 0X00;
	static int		bit_count = 0;
	static pid_t	client_pid = 0;

	(void)oldact;
	if (!client_pid)
		client_pid = siginfo->si_pid;
	c |= sig == SIGUSR1;
	if (bit_count++ < 7)
	{
		c = c << 1;
		kill(client_pid, SIGUSR2);
	}
	else
	{
		bit_count = 0;
		if (c == 0x00)
		{
			client_pid = 0;
			return ;
		}
		write(STDIN_FILENO, &c, 1);
		c = 0x00;
		kill(client_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server PID [", STDIN_FILENO);
	ft_putnbr_fd(getpid(), STDIN_FILENO);
	ft_putstr_fd("]\n", STDIN_FILENO);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (19)
		pause();
	return (0);
}
