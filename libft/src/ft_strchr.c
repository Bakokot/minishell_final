/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:40:40 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/14 07:56:06 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char	*s, int c)
{
	int		i;
	char	*cpy;
	char	d;

	i = 0;
	d = (char)c;
	cpy = (char *)s;
	if (d == 0)
	{
		while (cpy[i])
			i++;
		return (cpy + i);
	}
	while (cpy[i])
	{
		if (cpy[i] == d)
			return (cpy + i);
		i++;
	}
	return (0);
}
