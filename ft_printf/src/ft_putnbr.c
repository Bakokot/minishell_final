/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:06:37 by yallo             #+#    #+#             */
/*   Updated: 2023/12/14 16:09:27 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbr(int nbr, int *count, int fd)
{
	if (nbr == INT_MIN)
		return (ft_putstr("-2147483648", count, fd));
	if (nbr < 0)
	{
		ft_putchar('-', count, fd);
		nbr = -nbr;
	}
	ft_putnbr_base(nbr, "0123456789", count, fd);
}
