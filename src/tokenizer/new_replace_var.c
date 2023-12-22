/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_replace_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:49:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/22 16:01:47 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Replace the $VAR normally
 * Stops whenever we cross a quote to change the behaviour
*/
static char	*double_quote_behaviour(char *token, int *i, \
char *updated_token, t_env *env)
{
	int	marker;

	marker = *i;
	*i += 1;
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$')
		{
			updated_token = update_token(token, i, marker, updated_token);
			*i += 1;
			updated_token = change_var(token, i, updated_token, env);
			marker = *i;
		}
		else
			*i += 1;
	}
	*i += 1;
	updated_token = update_token(token, i, marker, updated_token);
	return (updated_token);
}

/**
 * Ignore the $VAR replacement
 * Stops whenever we cross a quote to change the behaviour
*/
static char	*single_quote_behaviour(char *token, int *i, char *updated_token)
{
	int	marker;

	marker = *i;
	*i += 1;
	while (token[*i] && token[*i] != '\'')
		*i += 1;
	*i += 1;
	updated_token = update_token(token, i, marker, updated_token);
	return (updated_token);
}

/**
 * Replace the $VAR normally
 * Stops whenever we cross a quote to change the behaviour
*/
static char	*no_quote_behaviour(char *token, int *i, \
char *updated_token, t_env *env)
{
	int	marker;

	marker = *i;
	while (token[*i] && token[*i] != '\"' && token[*i] != '\"')
	{
		if (token[*i] == '$')
		{
			updated_token = update_token(token, i, marker, updated_token);
			*i += 1;
			updated_token = change_var(token, i, updated_token, env);
			marker = *i;
		}
		else
			*i += 1;
	}
	updated_token = update_token(token, i, marker, updated_token);
	return (updated_token);
}

/**
 * Update all the $VAR of a single token
*/
static void	update_varn(t_token *token, t_env *env)
{
	int		i;
	char	*temp;
	int		flag_quote;
	char	*n_token;

	i = 0;
	temp = token->token;
	n_token = NULL;
	while (token->token[i])
	{
		flag_quote = is_quote(token->token[i]);
		if (flag_quote == '\"')
			n_token = double_quote_behaviour(token->token, &i, n_token, env);
		else if (flag_quote == '\'')
			n_token = single_quote_behaviour(token->token, &i, n_token);
		else
			n_token = no_quote_behaviour(token->token, &i, n_token, env);
	}
	if (!n_token)
		token->empty = true;
	token->token = n_token;
	free(temp);
}

/**
 * Update all the $VAR of all tokens
*/
void	replace_varsn(t_token **token_lst, t_env *env)
{
	t_token	*token;
	t_token	*temp;

	token = (*token_lst);
	while (token)
	{
		update_varn(token, env);
		if (token->empty == true)
		{
			temp = token->next;
			delete_token(token_lst, token);
			token = temp;
		}
		else
			token = token->next;
	}
}
