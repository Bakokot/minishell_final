/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:40:06 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/22 13:26:13 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a new t_token and fills the char * value
*/
t_token	*create_new_token(char *str, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (log_error(ERR_MALLOC), NULL);
	new_token->token = str;
	new_token->quoted = false;
	new_token->empty = false;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_back_token(t_token **token_lst, t_token *token)
{
	if (!token_lst || !token)
		return ;
	if (*token_lst)
		get_last_token(*token_lst)->next = token;
	else
		*token_lst = token;
}

t_token	*get_last_token(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	delete_first_token(t_token **token_lst)
{
	t_token	*temp;

	temp = (*token_lst);
	(*token_lst) = (*token_lst)->next;
	free(temp);
}

void	delete_token(t_token **token_lst, t_token *token)
{
	t_token	*temp;
	t_token	*prev;

	if (token == (*token_lst))
		return ;
	temp = (*token_lst);
	while (temp->next != token)
		temp = temp->next;
	prev = temp;
	prev->next = token->next;
	if (token->token)
		free(token->token);
	free(token);
}

size_t	token_size(t_token *token_lst)
{
	size_t	size;

	size = 0;
	while (token_lst)
	{
		size++;
		token_lst = token_lst->next;
	}
	return (size);
}
