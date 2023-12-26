/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:10:16 by yallo             #+#    #+#             */
/*   Updated: 2023/12/27 00:57:13 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int		ft_printf(int fd, const char *format, ...);
void	ft_putchar(int c, int *count, int fd);
void	ft_putnbr_base(long long unsigned int nbr, \
char *base, int *count, int fd);
void	ft_putnbr(int nbr, int *count, int fd);
void	ft_putstr(char *s, int *count, int fd);

#endif
