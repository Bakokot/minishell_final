/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_replace_var_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:32:48 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/21 09:23:06 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Update the token with what we have analyzed before stumbling upon a $VAR
*/
char	*update_token(char *token, int *i, int marker, char *updated_token)
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

static void	init_variables(char **temp, int *marker, int *i, char *token)
{
	*temp = token;
	*marker = *i;
}

/**
 * Actual replacement of a single $VAR
 * If we have $ or $$, we treat the $VAR as a litteral $ or two litterals $$
*/
char	*change_var(char *token, int *i, char *updated_token, t_env *env)
{
	char	*temp;
	char	*key;
	char	*value;
	int		marker;

	if (special_cases(token, &updated_token, i) == true)
		return (updated_token);
	init_variables(&temp, &marker, i, updated_token);
	while (token[*i] != '\'' && token[*i] != '\"' && !ft_isspace(token[*i]) \
	&& token[*i] != '$' && token[*i])
		*i += 1;
	key = ft_strndup(token + marker, *i - marker);
	value = lookup_values(key, env);
	free(key);
	if (value != NULL)
	{
		if (updated_token == NULL)
			updated_token = ft_strdup(value);
		else
		{
			updated_token = ft_strjoin(updated_token, value);
			free(temp);
		}
	}
	return (updated_token);
}
