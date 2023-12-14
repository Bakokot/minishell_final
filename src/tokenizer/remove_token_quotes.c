/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:27:57 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/14 12:42:22 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Remove the quotes from the tokens so the exec can run smoothly
*/
void	remove_token_quotes(t_token **token_lst)
{
	t_token	*cpy;
	char	*temp;

	cpy = *token_lst;
	while (cpy)
	{
		if (close_quotes(cpy->token) == true)
		{
			temp = cpy->token;
			cpy->token = ft_strndup(cpy->token + 1, ft_strlen(cpy->token + 1) - 1);
			free(temp);
		}
		cpy = cpy->next;
	}
}