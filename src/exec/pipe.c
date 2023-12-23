/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:01:40 by yallo             #+#    #+#             */
/*   Updated: 2023/12/23 00:17:03 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_child(t_token **token, t_env *env, int **pipes, int *pid)
{
	free_all_token(token);
	free_all_env(env);
	free_pipes(pipes);
	free(pid);
	exit(g_exit_status);
}

void	wait_all(int *pid, int **pipes, int count, t_heredoc *hd)
{
	int	i;

	i = 0;
	close_pipes(pipes, count);
	while (i <= count)
	{
		if (hd[i].fd_heredoc != -1)
		{
			close(hd[i].fd_heredoc);
			unlink(hd[i].heredoc);
		}
		free(hd[i].heredoc);
		waitpid(pid[i], &g_exit_status, WUNTRACED);
		kill(pid[i], SIGTERM);
		i++;
	}
	free(hd);
	free(pid);
	free_pipes(pipes);
}

int	create_child(int *pid, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (1);
		if (pid[i] == 0)
			return (1);
		i++;
	}
	return (1);
}

int	redirect_pipes_child(t_exec *exec, int **pipes, int i)
{
	if (!exec)
	{
		close_pipes(pipes, -1);
		return (1);
	}
	if (i != 0 && exec->in == -1)
		dup2(pipes[i - 1][0], 0);
	if (pipes[i] && exec->out == -1)
		dup2(pipes[i][1], 1);
	close_pipes(pipes, -1);
	return (0);
}

void	child_pipex(t_token *curr, t_exec *exec, t_env *env)
{
	if (exec_bultin(curr, env))
		exec_command(exec);
}

int	pipex(t_token **token, t_env *env, int count, t_heredoc *hd)
{
	int		i;
	int		*pid;
	int		**pipes;
	t_exec	*exec;
	t_token	*curr;

	i = -1;
	pipes = setup_pipes(*token);
	pid = malloc(sizeof(int) * (count + 1));
	if (!pid || !pipes)
		return (1);
	create_child(pid, count);
	while (++i <= count)
	{
		if (pid[i] == 0)
		{
			exec = handle_redirection(token, env, hd, i);
			curr = get_command(*token, i);
			if (!redirect_pipes_child(exec, pipes, i))
				child_pipex(curr, exec, env);
			free_exec(exec, *token);
			free_all_child(token, env, pipes, pid);
		}
	}
	return (wait_all(pid, pipes, count, hd), 0);
}
