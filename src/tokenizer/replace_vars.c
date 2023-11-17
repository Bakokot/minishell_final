/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:06:21 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/17 15:22:40 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_values(char *dollarless_token, char *values)
{
	char	*temp;

	temp = dollarless_token;
	if (dollarless_token == NULL)
		dollarless_token = ft_strdup(values);
	else
		dollarless_token = ft_strjoin(dollarless_token, values);
	if (temp != NULL)
		free(temp);
	return (dollarless_token);
}

/**
 * To replace $KEY :
 * - We skip the dollar sign
 * - We extract the KEY and lookup in the env
 * --> If it doesn't exist in the env : we do nothing
 * --> Else
 * - We add the VALUES connected to the KEY to the dollarless_token 
*/
static char	*replace_dollar(t_token *token, int *i, \
char *dollarless_token, t_env *env)
{
	char	*key;
	char	*tkn;
	char	*values;
	int		marker;

	*i += 1;
	tkn = token->token;
	marker = *i;
	while (tkn[*i] != ' ' && !is_quote(tkn[*i]) && tkn[*i] && tkn[*i] != '$')
		*i += 1;
	key = strndup(tkn + marker, *i - marker);
	values = lookup_values(key, env);
	if (values != NULL)
	{
		dollarless_token = add_values(dollarless_token, values);
	}
	free(key);
	return (dollarless_token);
}

/**
 * Update the dolalrless token by adding the part we analyzed that doesn't
 * contain any $VAR
*/
static char	*update_dollarless_token(t_token *token, int i, \
int marker, char *new_token)
{
	char	*new_token_adress;
	char	*strndup_adress;

	new_token_adress = new_token;
	strndup_adress = ft_strndup(token->token + marker, i - marker);
	if (new_token != NULL)
	{
		new_token = ft_strjoin(new_token, strndup_adress);
		free(new_token_adress);
		free(strndup_adress);
	}
	else
		new_token = strndup_adress;
	return (new_token);
}

/**
 * Check if we find a dollar in any of the token
 * If the dollar is between single quotes, we ignore it
 * -------------------------------------------------------
 * -------------------------------------------------------
 * To know how many char we wanna copy, we keep a marker
 * that remembers the index i before we started counting
*/
static void	lookup_dollars(t_token *token, t_env *env)
{
	int		i;
	int		marker;
	char	*dollarless;
	char	*temp;

	dollarless = NULL;
	i = 0;
	marker = 0;
	while (token->token[i])
	{
		marker = i;
		while (token->token[i] != '$' && token->token[i] != '\'' && token->token[i])
			i++;
		if (token->token[i] == '\'')
		{
			i++;
			while (token->token[i] != '\'')
				i++;
			i++;
			dollarless = update_dollarless_token(token, i, marker, dollarless);
		}
		else if (i != marker)
			dollarless = update_dollarless_token(token, i, marker, dollarless);
		else if (token->token[i] == '$')
			dollarless = replace_dollar(token, &i, dollarless, env);
	}
	temp = token->token;
	token->token = dollarless;
	free(temp);
}

void	replace_vars(t_token **token_lst, t_env *env)
{
	t_token	*token;

	token = (*token_lst);
	while (token)
	{
		lookup_dollars(token, env);
		token = token->next;
	}
}
