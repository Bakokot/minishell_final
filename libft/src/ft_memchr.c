/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:59:03 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/14 16:06:29 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpy;
	unsigned char	d;

	i = 0;
	d = (unsigned char)c;
	cpy = (unsigned char *)s;
	while (i < n)
	{
		if (cpy[i] == d)
			return (cpy + i);
		i++;
	}
	return (0);
}
