/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:56:31 by yallo             #+#    #+#             */
/*   Updated: 2023/12/01 16:33:59 by yallo            ###   ########.fr       */
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
	char *home;

	token_lst = token_lst->next;
	if (token_lst == NULL)
	{
		home = find_home(env);
		if (!home)
			return(printf("cd: HOME not set"), 1);
		chdir(home);
		return (0);
	}
	if (chdir(token_lst->token) == -1)
		return (printf("cd: %s: No such file or directory\n", token_lst->token), 1);
	return (0);
}
