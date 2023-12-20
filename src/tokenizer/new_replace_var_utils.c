/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_replace_var_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:32:48 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/20 13:23:54 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Update the token with what we have analyzed before stu;bling upon a $VAR
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

static char	*exit_status_var(char *updated_token)
{
	char	*temp;
	char	*exit_status;

	temp = updated_token;
	exit_status = ft_itoa(g_exit_status);
	if (updated_token == NULL)
		updated_token = exit_status;
	else
	{
		updated_token = ft_strjoin(updated_token, exit_status);
		free(temp);
		free(exit_status);
	}
	return (updated_token);
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
	else if (token[*i] == '?')
	{
		updated_token = exit_status_var(updated_token);
		*i += 1;
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
			updated_token = ft_strdup(value);
		else
		{
			updated_token = ft_strjoin(updated_token, value);
			free(temp);
		}
	}
	return (updated_token);
}
