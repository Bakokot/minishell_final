/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:29:20 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/09 16:46:39 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_new_env(char *key, char **values)
{
	t_env	*new_env;

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
	{
		get_last_env(*env_lst)->next = env;
	}
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