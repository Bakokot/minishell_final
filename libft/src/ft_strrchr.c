/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:34:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/14 07:57:15 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*cpy;
	char	d;

	i = 0;
	len = 0;
	cpy = (char *)s;
	d = (char)c;
	while (cpy[len])
		len++;
	if (d == 0)
		return (cpy + len);
	while (cpy[i])
	{
		if (cpy[len - i - 1] == d)
			return (cpy + (len - i - 1));
		i++;
	}
	return (0);
}
