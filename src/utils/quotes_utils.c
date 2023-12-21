/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:42:04 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/21 09:19:19 by thibault         ###   ########.fr       */
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
