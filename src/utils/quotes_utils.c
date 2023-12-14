/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:42:04 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/14 12:42:17 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return true if the line is between close quotes
 * @return false if the line isn't between close quotes
*/
bool close_quotes(char *line)
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
		return (true);
	return (false);
}