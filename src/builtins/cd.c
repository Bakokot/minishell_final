/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:56:31 by yallo             #+#    #+#             */
/*   Updated: 2023/12/27 14:54:54 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home(t_env *env)
{
	size_t	j;

	j = 0;
	while (env)
	{
		if (ft_strcmp("HOME", env->key) == 0)
			return (env->values);
		j++;
		env = env->next;
	}
	return (NULL);
}

int	cd(t_token	*token_lst, t_env *env)
{
	char	*home;

	token_lst = token_lst->next;
	if (token_lst && token_lst->type == 1)
		token_lst = NULL;
	if (token_lst == NULL)
	{
		home = find_home(env);
		if (!home)
		{
			g_exit_status = 1;
			return (ft_printf(2, "cd: HOME not set\nr"), 1);
		}
		chdir(home);
		return (0);
	}
	if (chdir(token_lst->token) == -1)
	{
		ft_printf(2, "cd: %s: No such file or directory\n", token_lst->token);
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = 0;
	return (0);
}
