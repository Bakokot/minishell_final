/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/16 20:11:52 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_fd(t_exec *exec)
{
	if (exec->fd_heredoc != -1)
	{
		unlink("heredoc");
		close(exec->fd_heredoc);
	}
	dup2(exec->sstdin, 0);
	dup2(exec->sstdout, 1);
	dup2(exec->sstderr, 2);
	close(exec->sstdin);
	close(exec->sstdout);
	close(exec->sstderr);
}

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

t_exec	*handle_redirection(t_token *token_lst, t_env *env)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	if (init_exec(exec))
		return (free_exec(exec), NULL);
	if (change_standard_fd(token_lst, &exec, env))
		return (free_exec(exec), NULL);
	exec->envp = env_lst_into_char(env);
	exec->args = token_lst_into_char(token_lst);
	if (!exec->args || !exec->envp)
		return (free_exec(exec), NULL);
	exec->path = get_path(token_lst->token, env);
	if (!exec->path && is_bultin(token_lst) == 1)
	{
		ft_printf(exec->sstderr, "%s : command not found\n", token_lst->token);
		return (free_exec(exec), NULL);
	}
	return (exec);
}

void	handle_command(t_token **token_lst, t_env *env)
{
	t_exec	*exec;

	exec = handle_redirection(*token_lst, env);
	if (!exec)
		return ;
	if (exec_bultin(*token_lst, env, exec->sstderr))
		exec_command(exec);
	restore_fd(exec);
	free_exec(exec);
}
