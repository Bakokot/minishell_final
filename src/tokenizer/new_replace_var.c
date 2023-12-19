/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_replace_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:49:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/19 13:04:36 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Update the token with what we have analyzed before stu;bling upon a $VAR
*/
static char	*update_token(char *token, int *i, int marker, char *updated_token)
{
	char	*temp1;
	char	*temp2;

	temp1 = updated_token;
	if (marker != *i)
	{
		if (token == NULL)
		{
			updated_token = ft_strndup(token + marker, *i - marker);
			return (token);
		}
		else
		{
			if (updated_token == NULL)
				updated_token = ft_strndup(token + marker, *i - marker);
			else
			{
				temp2 = ft_strndup(token + marker, *i - marker);
				updated_token = ft_strjoin(updated_token, temp2);
				free(temp1);
				free(temp2);
			}
		}
	}
	return (updated_token);
}

/**
 * Add two litteral dollars to the updated_token 
*/
static char	*double_dollar(char *updated_token)
{
	char	*temp;

	temp = updated_token;
	if (updated_token == NULL)
		updated_token = ft_strdup("$$");
	else
	{
		updated_token = ft_strjoin(updated_token, "$$");
		free(temp);
	}
		return (updated_token);
}

/**
 * Add a single litteral dollar to the updated_token
*/
static char	*single_dollarn(char *updated_token)
{
	char	*temp;

	temp = updated_token;
	if (updated_token == NULL)
		updated_token = ft_strdup("$");
	else
	{
		updated_token = ft_strjoin(updated_token, "$");
		free(temp);
	}
	return (updated_token);
}

/**
 * Actual replacement of a single $VAR
 * If we have $ or $$, we treat the $VAR as a litteral $ or two litterals $$
*/
static char	*change_var(char *token, int *i, char *updated_token, t_env *env)
{
	char	*temp;
	char	*key;
	char	*value;
	int		marker;

	if (token[*i] == '$')
	{
		updated_token = double_dollar(updated_token);
		*i += 1;
		return(updated_token);
	}
	else if (token[*i] == '\'' || token[*i] == '\"' || ft_isspace(token[*i]) || !token[*i])
	{
		updated_token = single_dollarn(updated_token);
		return (updated_token);
	}
	temp = updated_token;
	marker = *i;
	while (token[*i] != '\'' && token[*i] != '\"' && !ft_isspace(token[*i]) && token[*i] != '$' && token[*i])
		*i += 1;
	key = ft_strndup(token + marker, *i - marker);
	value = lookup_values(key, env);
	free(key);
	if (value != NULL)
	{
		if (updated_token == NULL)
		{	
			updated_token = ft_strdup(value);
		}
		else
		{
			updated_token = ft_strjoin(updated_token, value);
			free(temp);
		}
	}
	return (updated_token);
}

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