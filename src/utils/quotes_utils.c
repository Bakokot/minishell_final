/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:42:04 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/27 12:53:31 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return true if the line isn't between unclosed quotes
 * @return false if the line is between unclosed quotes
*/
bool	unclosed_quotes(char *line)
{
	int	i;
	int	quote_type;

	i = 0;
	quote_type = 0;
	while (line[i])
	{
		quote_type = is_quote(line[i]);
		i++;
		while (quote_type != 0 && line[i])
		{
			if (quote_type == line[i])
				quote_type = 0;
			i++;
		}
	}
	if (quote_type == 0)
		return (false);
	return (true);
}

/**
 * @return true if the str contains closed quotes
 * @return false if the string doesn't contain closed quotes
*/
bool	closed_quotes(char *str)
{
	int	i;
	int	quote_type;

	i = 0;
	quote_type = 0;
	while (str && str[i])
	{
		quote_type = is_quote(str[i]);
		while (quote_type != 0 && str[i])
		{
			i++;
			if (quote_type == str[i])
				return (true);
		}
		i++;
	}
	return (false);
}

/**
 * @return true if the line has unclosed pipe
 * @return false if the line ahs not unclosed pipe
*/
bool	unclosed_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i + 1])
		i++;
	while (ft_isspace(line[i]) && i >= 0)
		i--;
	if (line[i] == '|')
		return (true);
	return (false);
}

char	strchr_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\"' && line[i] != '\'')
		i++;
	return (line[i]);
}

bool	double_pipe(t_token **lst)
{
	t_token	*cpy;

	cpy = *lst;
	while (cpy->next)
	{
		if (cpy->type == PIPE && cpy->next->type == PIPE)
			return (true);
		cpy = cpy->next;
	}
	return (false);
}
