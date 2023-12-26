/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:09:35 by yallo             #+#    #+#             */
/*   Updated: 2023/12/27 00:12:32 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_redirection(t_token *token)
{
	if (token->next == NULL || (token->next->type != 0 \
	&& token->next->type != 3))
		return (1);
	return (0);
}

int	check_args(t_token *token)
{
	if (token == NULL)
		return (1);
	if (token->type == 1)
	{
		ft_printf(2, "Error: No command before PIPE\n");
		return (1);
	}
	while (token)
	{
		if (token->type != 0 && token->type != 1 && \
		valid_redirection(token) == 1)
		{
			ft_printf(2, "Error: invalid redirections\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}
