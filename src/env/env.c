/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:30:00 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/15 22:45:33 by yallo            ###   ########.fr       */
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
char	*get_env_key(char *envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] != '=' && envp[i] != '+')
		i++;
	return (ft_strndup(envp, i));
}

char	*get_env_values(char *envp)
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
		new = create_new_env(key, values, 2);
		add_back_env(&env, new);
		i++;
	}
	return (env);
}

char	**env_lst_into_char(t_env *env)
{
	size_t	i;
	size_t	size;
	char	**envp;

	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		size = ft_strlen(env->key) + ft_strlen(env->values) + 2;
		envp[i] = malloc(sizeof(char) * size);
		if (!envp[i])
			return (free_array(envp), NULL);
		ft_strlcpy(envp[i], env->key, size);
		ft_strlcat(envp[i], "=", size);
		ft_strlcat(envp[i], env->values, size);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
