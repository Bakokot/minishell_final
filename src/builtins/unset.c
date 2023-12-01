/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:58:45 by yallo             #+#    #+#             */
/*   Updated: 2023/12/01 15:56:25 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_key(char *find, t_env *env)
{
	size_t	j;

	j = 0;
	while (env)
	{
		if (ft_strcmp(find, env->key) == 0)
			return (j);
		j++;
		env = env->next;
	}
	return (-1);
}

static void	unset_variable(t_env **env, size_t index)
{
	t_env	*tmp;
	t_env	*before;
	t_env	*current;

	tmp = *env;
	while (index - 1 > 0 && tmp)
	{
		tmp = tmp->next;
		index--;
	}
	before = tmp;
	current = tmp->next;
	before->next = current->next;
	free(current);
}

int	unset(t_token *token_lst, t_env **env)
{
	t_env	*tmp;
	int	i;

	token_lst = token_lst->next;
	i = find_key(token_lst->token, *env);
	if (i == -1)
		return (0);
	if (i == 0)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp);
		return (0);
	}
	else
		unset_variable(env, i);
	return (0);
}

