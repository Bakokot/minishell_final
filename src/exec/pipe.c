/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:01:40 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 15:47:11 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_child(t_token **token, t_env *env, int **pipes, int *pid)
{
	free_all_token(token);
	free_all_env(env);
	free_pipes(pipes);
	free(pid);
	exit(0);
}

// void	child_pipex(t_token **token, t_env *env, int **pipes, int *pid)
// {
// 	int		count;

// 	redirect_pipes_child(*token, exec, pipes, i);
// 	if (!exec)
// 		exit(0);
// 	count = count_pipes(*token);
// 	close_pipes(pipes, count);
// 	exec_command(exec);
// }

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
		waitpid(pid[i], NULL, WUNTRACED);
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

void	redirect_pipes_child(t_token *token, t_exec *exec, int **pipes, int i)
{
	int	count;

	count = count_pipes(token);
	if (i != 0 && exec->in == -1)
		dup2(pipes[i - 1][0], 0);
	if (i < count && exec->out == -1)
		dup2(pipes[i][1], 1);
	close_pipes(pipes, -1);
}

int	pipex(t_token **token, t_env *env, int count, t_heredoc *hd)
{
	int		i;
	int		*pid;
	int		**pipes;
	t_token	*curr;
	t_exec	*exec;

	i = 0;
	pipes = setup_pipes(*token);
	if (!pipes)
		return (1);
	pid = malloc(sizeof(int) * (count + 1));
	if (!pid)
		return (1);
	create_child(pid, count);
	while (i <= count)
	{
		if (pid[i] == 0)
		{
			curr = get_command(*token, i);
			exec = handle_redirection(&curr, env, hd);
			if (exec)
			{
				redirect_pipes_child(*token, exec, pipes, i);
				if (exec_bultin(curr, env))
					exec_command(exec);
			}
			free_exec(exec, *token);
			free_all_child(token, env, pipes, pid);
		}
		i++;
	}
	close_pipes(pipes, -1);
	wait_all(pid, pipes, count, hd);
	return (0);
}
