/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:10:22 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/14 07:54:54 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	d;
	char			*cpy;

	i = 0;
	d = c;
	cpy = (char *)b;
	while (i < len)
	{
		cpy[i] = d;
		i++;
	}
	return (b);
}
