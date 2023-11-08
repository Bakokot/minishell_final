/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:22:01 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/08 23:25:16 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_token **token_lst)
{
	t_token	*temp;

	while (*token_lst)
	{
		temp = (*token_lst)->next;
		free((*token_lst)->token);
		free(*token_lst);
		*token_lst = temp;
	}
	free(token_lst);
}
