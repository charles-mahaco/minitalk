/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:55:33 by charles           #+#    #+#             */
/*   Updated: 2021/07/28 20:55:36 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_error(char *str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

size_t	ft_strlen(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	char	c;

	i = n;
	if (i < 0)
	{
		write(1, "-", 1);
		i = -i;
	}
	if (i >= 10)
	{
		ft_putnbr_fd((i / 10), fd);
		c = (i % 10 + '0');
		write(1, &c, 1);
	}
	else
	{
		c = (i + '0');
		write(1, &c, 1);
	}
}

int	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	long long int		digit;

	i = 0;
	digit = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		else
			signe = 1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		digit = digit * 10 + (str[i] - '0');
		i++;
	}
	return (digit * signe);
}
