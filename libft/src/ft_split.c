/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 07:58:25 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/21 01:11:24 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_nbr_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			i++;
			count++;
			while (s[i] && s[i] != c)
			i++;
		}
		else
			i++;
	}
	return (count);
}

static void	*free_array(char **array)
{
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	free(array);
	return (NULL);
}

static char	**fill_array(char const *s, char c, char **array)
{
	size_t	i;
	size_t	word;
	size_t	start;

	i = 0;
	word = 0;
	while (s[i])
	{
		start = i;
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			array[word] = ft_substr(s, start, i - start);
			if (!array[word])
				return (free_array(array));
			word++;
		}
		else
			i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	count;

	if (!s || !c)
		return (NULL);
	count = count_nbr_word(s, c);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	array[count] = NULL;
	array = fill_array(s, c, array);
	return (array);
}
