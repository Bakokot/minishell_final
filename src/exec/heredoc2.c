/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:16:10 by thibault          #+#    #+#             */
/*   Updated: 2023/12/22 16:16:28 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_heredoc(t_token *token, char *line)
{
	char	*delimiter;

	delimiter = token->next->token;
	if (line == NULL)
	{
		ft_printf(2, "Warning: heredoc delimiter was %s\n", delimiter);
		return (1);
	}
	if (ft_strlen(delimiter) == ft_strlen(line))
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			return (1);
	return (0);
}
