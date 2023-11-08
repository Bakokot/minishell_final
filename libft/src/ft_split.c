/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 07:58:25 by tbarde-c          #+#    #+#             */
/*   Updated: 2022/11/16 15:46:01 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(const char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			i++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (0);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	free_all(char **ret, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}

static int	test_mem(char **ret, int j, int *index)
{
	*index = -1;
	if (!ret[j])
	{
		free_all(ret, j);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**ret;

	ret = malloc((wordcount(s, c) + 1) * sizeof(char *));
	if (!s || !ret)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			ret[j++] = word_dup(s, index, i);
			if (test_mem(ret, j - 1, &index) == 0)
				return (0);
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}
