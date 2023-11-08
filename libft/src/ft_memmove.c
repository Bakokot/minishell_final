/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:55:27 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/15 12:43:45 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*cpysrc;
	char	*cpydst;
	int		flag;

	if (!dst && !src)
		return (0);
	cpydst = (char *)dst;
	cpysrc = (char *)src;
	flag = 0;
	i = 0;
	while (i++ < len)
		if (&cpysrc[i] == &cpydst[0])
			flag = 1;
	i = 0;
	while (i < len)
	{
		if (flag == 1)
			cpydst[len - 1 - i] = cpysrc[len - i - 1];
		else
			cpydst[i] = cpysrc[i];
		i++;
	}
	return (dst);
}
