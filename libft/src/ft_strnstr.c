/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:23:51 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/15 13:04:35 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	size_t	k;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	if (!haystack && len == 0)
		return (0);
	while (haystack[i] && i < len)
	{
		j = 0;
		k = i;
		while (needle[j] && haystack[k] && haystack[k] == needle[j] && k < len)
		{
			j++;
			k++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
