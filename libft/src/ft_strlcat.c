/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:08:31 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/15 12:56:58 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	if ((dst == NULL || src == NULL) && size == 0)
		return (0);
	while (dst[len] && len < size)
		len++;
	while (src[i] && size && len + i < size -1)
	{
		dst[len + i] = src[i];
		i++;
	}
	if (len < size)
		dst[len + i] = 0;
	i = 0;
	while (src[i])
		i++;
	return (len + i);
}
