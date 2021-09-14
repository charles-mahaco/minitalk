/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 20:20:58 by charles           #+#    #+#             */
/*   Updated: 2021/08/30 20:21:03 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>

size_t	ft_strlen(char	*s);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
void	exit_error(char *str);
int		ft_atoi(const char	*str);

#endif
