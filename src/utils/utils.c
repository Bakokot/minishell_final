/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:20:03 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/19 01:25:43 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if a character is " or '
 * @returns 0 if no quote, else return the ascii number of the quote
*/
int	is_quote(char c)
{
	if (c == '\'')
		return ('\'');
	else if (c == '\"')
		return ('\"');
	return (0);
}

/**
 * @brief Check if a character is '|' or '>' or '<'
 * @returns 0 if no metachar, else return the ascii number of the metachar
*/
int	is_metachar(char c)
{
	if (c == '|')
		return ('|');
	if (c == '>')
		return ('>');
	if (c == '<')
		return ('<');
	return (0);
}

/**
 * @returns 1 if char is space else 0
*/
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

/*
	Check if the two first char are redirections (>> or <<)
*/
int	is_double_redirection(char *str)
{
	return ((str[0] == '>' && str[1] == '>') \
	|| (str[0] == '<' && str[1] == '<'));
}

/**
 * Duplicate size * chars of the string given
*/
char	*ft_strndup(char *s1, size_t size)
{
	size_t		i;
	char		*cpy;

	if (size == 0)
		return (NULL);
	i = 0;
	cpy = (char *)malloc(sizeof(*s1) * (size + 1));
	if (!cpy)
		return (log_error(ERR_MALLOC), NULL);
	while (i < size)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
