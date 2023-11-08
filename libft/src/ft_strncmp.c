/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:55:08 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/15 08:53:41 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (((unsigned char)(s1[i]) - (unsigned char)s2[i]));
		i++;
	}
	if (s1[i] == '\0' && i != n)
		return (-(unsigned char)(s2[i]));
	else
		return (0);
}
