/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:30:00 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/09 16:47:26 by tbarde-c         ###   ########.fr       */
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

/*static int	count_values(char *envp, int i)
{
	int	count;

	count = 1;
	while (envp[i])
	{
		if (envp[i] == ':')
			count++;
		i++;
	}
	return (count);
}*/

/*static void	set_env_values(t_env *env, char *envp)
{
	int	i;
	int	j;
	int	temp;
	int	count;

	if (!envp)
		return ;
	i = 0;
	j = 0;
	while (envp[i] != '=')
		i++;
	count = count_values(envp, i);
	env->values = malloc(sizeof(char *) * count);
	if (!env->values)
		return (log_error(ERR_MALLOC));
	temp = i;
	while (j < count)
	{
		if (envp[i] == ':' || envp[i] == '\0')
		{
			env->values[j] = ft_strndup(envp + temp, temp - i);
			temp = i;
			j++;
		}
		i++;
	}
}*/

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*new;
	char	*key;
	//char	**values;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		key = get_env_key(envp[i]);
		//values = get_env_values(env, envp[i]);
		new = create_new_env(key, NULL);
		add_back_env(&env, new);
		i++;
	}
	return (env);
}