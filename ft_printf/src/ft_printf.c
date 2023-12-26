/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:32:03 by yallo             #+#    #+#             */
/*   Updated: 2022/12/19 13:36:05 by yallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	check_arg(char c, va_list arg, int *count, int fd)
{
	if (c == 'c')
		ft_putchar(va_arg(arg, int), count, fd);
	if (c == 's')
		ft_putstr(va_arg(arg, char *), count, fd);
	if (c == 'p')
	{
		ft_putstr("0x", count, fd);
		ft_putnbr_base(va_arg(arg, long long unsigned int), \
		"0123456789abcdef", count, fd);
	}
	if ((c == 'd' || c == 'i'))
		ft_putnbr(va_arg(arg, int), count, fd);
	if (c == 'u')
		ft_putnbr_base(va_arg(arg, unsigned int), "0123456789", count, fd);
	if (c == 'x')
		ft_putnbr_base(va_arg(arg, unsigned int), \
		"0123456789abcdef", count, fd);
	if (c == 'X')
		ft_putnbr_base(va_arg(arg, unsigned int), \
		"0123456789ABCDEF", count, fd);
	if (c == '%')
		ft_putchar('%', count, fd);
}

int	ft_printf(int fd, const char *format, ...)
{
	int		i;
	int		count;
	va_list	arg;

	i = 0;
	count = 0;
	va_start(arg, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			check_arg(format[i], arg, &count, fd);
		}
		else
			ft_putchar(format[i], &count, fd);
		i++;
	}
	va_end(arg);
	return (count);
}
