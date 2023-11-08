/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:52:32 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/15 12:41:50 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*cpysrc;
	char	*cpydst;

	if (!dst && !src)
		return (0);
	cpydst = (char *)dst;
	cpysrc = (char *)src;
	i = 0;
	while (i < n)
	{
		cpydst[i] = cpysrc[i];
		i++;
	}
	return (dst);
}
