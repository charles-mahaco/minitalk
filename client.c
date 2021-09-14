/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:56:00 by charles           #+#    #+#             */
/*   Updated: 2021/07/28 20:56:03 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	connection_terminated(pid_t server_pid)
{
	static int	i = 8;

	if (i--)
	{
		if (kill(server_pid, SIGUSR2) == -1)
			exit_error("Unexpected error");
		usleep(100);
	}
	if (!i)
	{
		ft_putstr_fd("\nTransmission done\n", STDIN_FILENO);
		exit(0);
	}
}

void	bit_sender(char *message, pid_t pid)
{
	static int				i = -1;
	static unsigned char	c;
	static char				*str;
	static int				server_rep = 0;

	if (message)
	{
		str = message;
		c = *str;
	}
	if (i == 7)
	{
		i = -1;
		c = *(++str);
	}
	if (c && c << ++i & 0x80)
		server_rep = kill(pid, SIGUSR1);
	else if (c)
		server_rep = kill(pid, SIGUSR2);
	else
		connection_terminated(pid);
	if (server_rep == -1)
		exit_error("Server not found\n");
}

void	sig_handler(int sig, siginfo_t *siginfo, void *oldact)
{
	static int	bytes_received = 0;

	(void)oldact;
	if (sig == SIGUSR1)
	{
		ft_putstr_fd("\rBytes received: ", STDIN_FILENO);
		ft_putnbr_fd(++bytes_received, STDIN_FILENO);
	}
	bit_sender(0, siginfo->si_pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3 || ft_strlen(argv[1]) > 7
		|| ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 4194303)
		exit_error("Usage : ./client [0 < Server PID < 4194304] [Message]\n");
	if (!ft_strlen(argv[2]))
		return (0);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putstr_fd("Total bytes: ", STDIN_FILENO);
	ft_putnbr_fd(ft_strlen(argv[2]), STDIN_FILENO);
	ft_putstr_fd("\n", STDIN_FILENO);
	bit_sender(argv[2], ft_atoi(argv[1]));
	while (19)
		pause();
	return (0);
}
