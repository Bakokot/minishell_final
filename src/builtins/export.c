/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:04:37 by yallo             #+#    #+#             */
/*   Updated: 2023/11/30 15:25:50 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static char	*get_env_key(char *envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] != '=')
		i++;
	return (ft_strndup(envp, i));
}

static char	*get_env_values(char *envp)
{
	char	*values;
	int		i;

	i = 0;
	while (envp[i] != '=')
		i++;
	i++;
	values = ft_strdup(envp + i);
	return (values);
}

int	export(t_token *token_lst, t_env **env)
{
	t_env	*new;

	new = *env;
	token_lst = token_lst->next;
	if (!token_lst || token_lst->type != 0)
	{
		env_builtin(*env);
		return (0);
	}
	while (new)
	{
		new = new->next;
	}
	new = create_new_env(get_env_key(token_lst->token), get_env_values(token_lst->token));
	add_back_env(env, new);
	return (0);
}
