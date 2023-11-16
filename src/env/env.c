/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:30:00 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/16 23:24:59 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Set the key to the environment struct
 * KEY --> What's before the =
 * For example : 
 * PATH= /home/whatever/whatever:/another/path
 * |----|-----------------------|-------------|
 *  KEY      VALUE NUMBER 1      VALUE NMBER 2
*/
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

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*new;
	char	*key;
	char	*values;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		key = get_env_key(envp[i]);
		values = get_env_values(envp[i]);
		new = create_new_env(key, values);
		add_back_env(&env, new);
		i++;
	}
	return (env);
}
