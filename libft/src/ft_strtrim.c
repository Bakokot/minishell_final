/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:35 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/15 08:27:08 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		begin;
	int		i;
	int		end;

	begin = 0;
	i = 0;
	end = 0;
	while (test(s1[begin], set) && s1[begin])
		begin++;
	end = ft_strlen(s1);
	while (test(s1[end - 1], set) && end > begin)
		end--;
	ret = malloc(sizeof(*s1) *(end - begin + 1));
	if (!ret)
		return (0);
	while (end > begin)
	{
		ret[i] = s1[begin];
		i++;
		begin++;
	}
	ret[i] = 0;
	return (ret);
}
