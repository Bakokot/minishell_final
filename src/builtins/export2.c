/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:14:50 by yallo             #+#    #+#             */
/*   Updated: 2023/12/27 13:00:15 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_node(t_env *cur, t_env *next)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = cur->key;
	tmp_value = cur->values;
	cur->key = next->key;
	cur->values = next->values;
	next->key = tmp_key;
	next->values = tmp_value;
}

static t_env	*lst_copy(t_env *env)
{
	t_env	*env_copy;
	t_env	*new;

	env_copy = NULL;
	while (env)
	{
		new = create_new_env(ft_strdup(env->key), ft_strdup(env->values));
		if (!new)
			return (free_all_env(env_copy), NULL);
		add_back_env(&env_copy, new);
		env = env->next;
	}
	return (env_copy);
}

void	print_export(t_env *env)
{
	size_t	size;
	t_env	*env_copy;
	t_env	*head;

	env_copy = lst_copy(env);
	if (!env_copy)
		return ;
	head = env_copy;
	while (env_copy->next)
	{
		size = ft_strlen(env_copy->key);
		if (ft_strncmp(env_copy->key, env_copy->next->key, size) > 0)
		{
			swap_node(env_copy, env_copy->next);
			env_copy = head;
		}
		else
			env_copy = env_copy->next;
	}
	env_builtin(head);
	free_all_env(head);
}

void	export_new(t_env **env, char *arg)
{
	char	*key;
	char	*value;
	t_env	*new;

	new = *env;
	while (new)
		new = new->next;
	key = get_env_key(arg);
	value = get_env_values(arg);
	new = create_new_env(key, value);
	add_back_env(env, new);
}
