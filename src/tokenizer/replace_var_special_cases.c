/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_special_cases.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:44:56 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/22 21:24:38 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check for special cases :
 * - A single litteral $
 * - Two $$
 * - $? --> change for last exit status
*/
bool	special_cases(char *token, char **updated_token, int *i)
{
	if (token[*i] == '$')
	{
		*updated_token = double_dollar(*updated_token);
		*i += 1;
		return (true);
	}
	else if (token[*i] == '\'' || token[*i] == '\"' || \
	ft_isspace(token[*i]) || !token[*i])
	{
		*updated_token = single_dollarn(*updated_token);
		return (true);
	}
	else if (token[*i] == '?')
	{
		*updated_token = exit_status_var(*updated_token);
		*i += 1;
		return (true);
	}
	return (false);
}

/**
 * Add two litteral dollars to the updated_token
*/
char	*double_dollar(char *updated_token)
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
char	*single_dollarn(char *updated_token)
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

char	*exit_status_var(char *updated_token)
{
	char	*temp;
	char	*exit_status;

	temp = updated_token;
	exit_status = ft_itoa(translate_error(g_exit_status));
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
