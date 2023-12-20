/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/20 15:42:05 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *cmd, t_env *env)
{
	size_t	i;
	size_t	size;
	char	*path;
	char	**all_path;

	i = 0;
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	all_path = ft_split(lookup_values("PATH", env), ':');
	while (all_path[i])
	{
		size = ft_strlen(all_path[i]) + ft_strlen(cmd) + 2;
		path = malloc(sizeof(char) * size);
		if (!path)
			return (free_array(all_path), NULL);
		ft_strlcpy(path, all_path[i], size);
		ft_strlcat(path, "/", size);
		ft_strlcat(path, cmd, size);
		if (access(path, F_OK | X_OK) >= 0)
			return (free_array(all_path), path);
		free(path);
		i++;
	}
	free_array(all_path);
	return (NULL);
}

t_exec	*handle_redirection(t_token **token_lst, t_env *env)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	init_exec(exec);
	if (change_standard_fd(*token_lst, exec, env))
		return (free_exec(exec), NULL);
	remove_redirection(token_lst);
	exec->envp = env_lst_into_char(env);
	exec->args = token_lst_into_char(*token_lst);
	if (!exec->args || !exec->envp)
		return (free_exec(exec), NULL);
	exec->path = get_path((*token_lst)->token, env);
	if (!exec->path && is_bultin(*token_lst) == 1)
	{
		ft_printf(2, "%s : command not found\n", (*token_lst)->token);
		return (free_exec(exec), NULL);
	}
	return (exec);
}

int	execute(t_token **token, t_env *env)
{
	t_exec	*exec;

	exec = handle_redirection(token, env);
	if (!exec)
		return (1);
	if (exec_bultin(*token, env) == 1)
		exec_command(exec);
	restore_fd(exec);
	free_exec(exec);
	return (0);
}

void	handle_command(t_token **token, t_env *env)
{
	int	count;

	count = count_pipes(*token);
	if (count == 0)
		execute(token, env);
	else
		pipex(*token, env, count);
}
