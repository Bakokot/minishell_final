/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_replace_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:49:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/19 13:46:56 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Replace the $VAR normally
 * Stops whenever we cross a quote to change the behaviour
*/
static char	*double_quote_behaviour(char *token, int *i, char *updated_token, t_env *env)
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
static char	*no_quote_behaviour(char *token, int *i, char *updated_token, t_env *env)
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
	int		flag_quote;
	int		i;
	char	*updated_token;
	char	*temp;

	temp = token->token;
	i = 0;
	flag_quote = 0;
	flag_quote = is_quote(token->token[i]);
	updated_token = NULL;
	while (token->token[i])
	{
		flag_quote = is_quote(token->token[i]);
		if (flag_quote == '\"')
		{
			updated_token = double_quote_behaviour(token->token, &i, updated_token, env);
			flag_quote = 0;
			printf("%s\n", updated_token);
		}
		else if (flag_quote == '\'')
		{
			updated_token = single_quote_behaviour(token->token, &i, updated_token);
			flag_quote = 0;
			printf("%s\n", updated_token);
		}
		else
		{
			updated_token = no_quote_behaviour(token->token, &i, updated_token, env);
			printf("%s\n", updated_token);
		}
	}
	printf("FINAL TOKEN --> %s\n", updated_token);
	token->token = updated_token;
	free(temp);
}

/**
 * Update all the $VAR of all tokens
*/
void	replace_varsn(t_token **token_lst, t_env *env)
{
	t_token	*token;

	token = (*token_lst);
	while (token)
	{
		update_varn(token, env);
		token = token->next;
	}
}