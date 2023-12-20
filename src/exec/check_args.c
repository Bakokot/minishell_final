/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:09:35 by yallo             #+#    #+#             */
/*   Updated: 2023/12/20 22:56:23 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(t_token *token)
{
	if (token == NULL)
		return (1);
	if (token->type == 1)
	{
		ft_printf(2, "Error: No command before pipe\n");
		return (1);
	}
	while (token)
	{
		if (token->type == 3 && (token->next == NULL || token->next->type != 0))
		{
			ft_printf(2, "Error: Invalid delimiter for heredoc\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}
