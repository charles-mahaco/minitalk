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

	(void)oldact;
	c |= sig == SIGUSR1;
	if (bit_count++ < 7)
	{
		c = c << 1;
		kill(siginfo->si_pid, SIGUSR2);
	}
	else
	{
		bit_count = 0;
		if (c == 0x00)
			return ;
		write(STDIN_FILENO, &c, 1);
		c = 0x00;
		kill(siginfo->si_pid, SIGUSR1);
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
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (19)
		pause();
	return (0);
}
