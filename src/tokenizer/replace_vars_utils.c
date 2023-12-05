/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:04:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/05 13:47:03 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_single_quotes(int *i, char *str)
{
	*i += 1;
	while (str[*i] != '\'')
		*i += 1;
	*i += 1;
}

/**
 * Check if the line entered is a single char '$'
 * if so, we know that the $ must be treated litterally
 * @return true if we found a single char $
 * @return else returns false
*/
bool	single_dollar(t_token *token)
{
	char	*temp;

	if (token->token[0] == '$' && token->token[1] == '\0')
	{
		temp = token->token;
		token->token = ft_strdup("$");
		free(temp);
		return (true);
	}
	return (false);
}

/**
 * Update the dolalrless token by adding the part we analyzed that doesn't
 * contain any $VAR
 * @return char *updated_token
*/
char	*update_dollarless_token(t_token *token, int i, \
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
 * When we have a $ followed by space or nothing,
 * we treat the $ as a litteral char
*/
char	*add_litteral_dollar(char *dollarless_token, int *i, char *tkn)
{
	char	*temp;

	temp = dollarless_token;
	if (tkn[*i] != '$')
	{
		dollarless_token = ft_strjoin(dollarless_token, "$");
	}
	if (tkn[*i] == '$')
	{
		if (dollarless_token == NULL)
			dollarless_token = ft_strdup("$$");
		else
			dollarless_token = ft_strjoin(dollarless_token, "$$");
		*i += 1;
	}
	if (temp != NULL)
		free(temp);
	return (dollarless_token);
}

/**
 * Update the token with the replacement of the $VAR
*/
void	set_new_token(t_token *token, char *dollarless)
{
	char	*temp;

	temp = token->token;
	token->token = dollarless;
	free(temp);
}
