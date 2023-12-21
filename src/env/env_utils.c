/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:29:20 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/21 09:30:52 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_new_env(char *key, char *values)
{
	t_env	*new_env;

	if (!key || !values)
		return (NULL);
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (log_error(ERR_MALLOC), NULL);
	new_env->key = key;
	new_env->values = values;
	new_env->next = NULL;
	return (new_env);
}

void	add_back_env(t_env **env_lst, t_env *env)
{
	if (!env_lst || !env)
		return ;
	if (*env_lst)
		get_last_env(*env_lst)->next = env;
	else
		*env_lst = env;
}

t_env	*get_last_env(t_env *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

/**
 * Look for the key in the env struct to check its existence
 * @return NULL if the KEY doesn't exist //
 * @return KEY VALUES if the KEY exists
*/
char	*lookup_values(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env->values);
		env = env->next;
	}
	return (NULL);
}

size_t	env_size(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}
