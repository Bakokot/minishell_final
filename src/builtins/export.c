/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:04:37 by yallo             #+#    #+#             */
/*   Updated: 2023/12/27 12:58:56 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_key(char *find, t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env)
	{
		j = 0;
		while (env->key[j] && env->key[j] != '=' && env->key[j] != '+')
			j++;
		if (ft_strncmp(find, env->key, j) == 0)
			return (i);
		i++;
		env = env->next;
	}
	i = 0;
	while (find[i])
	{
		if (find[i] == '=')
			return (-1);
		i++;
	}
	return (-2);
}

static int	is_plus(t_token *token_lst)
{
	size_t	i;

	i = 0;
	while (token_lst->token[i])
	{
		if (token_lst->token[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

static void	change_value(t_env **env, t_token *token_lst, int index)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && index > 0)
	{
		index--;
		tmp = tmp->next;
	}
	free(tmp->values);
	tmp->values = get_env_values(token_lst->token);
}

static void	add_value(t_env **env, t_token *token_lst, int index)
{
	t_env	*tmp;
	char	*new_value;
	size_t	size_token;
	size_t	size_env;

	tmp = *env;
	while (tmp && index > 0)
	{
		index--;
		tmp = tmp->next;
	}
	size_token = ft_strlen(token_lst->token);
	size_env = ft_strlen(tmp->values);
	new_value = malloc(sizeof(char *) * (size_token * size_env + 1));
	if (!new_value)
	{
		ft_printf(2, "Malloc failed\n");
		return ;
	}
	ft_strlcpy(new_value, tmp->values, size_token * size_env + 1);
	ft_strlcat(new_value, get_env_values(token_lst->token), \
	size_token * size_env + 1);
	free(tmp->values);
	tmp->values = new_value;
}

int	export(t_token *token_lst, t_env **env)
{
	int		index;

	token_lst = token_lst->next;
	if (!token_lst || token_lst->type != 0)
		return (print_export(*env), 0);
	while (token_lst && token_lst->type != 1)
	{
		index = find_key(token_lst->token, *env);
		if (index == -1)
			export_new(env, token_lst->token);
		else if (index != -2)
		{
			if (is_plus(token_lst))
				add_value(env, token_lst, index);
			else
				change_value(env, token_lst, index);
		}
		token_lst = token_lst->next;
	}
	g_exit_status = 0;
	return (0);
}
