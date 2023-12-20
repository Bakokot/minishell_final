/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:01:40 by yallo             #+#    #+#             */
/*   Updated: 2023/12/21 00:22:49 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_pipex(t_token *token, t_env *env, int **pipes, int cmd_nbr)
{
	int		count;
	t_exec	*exec;

	count = count_pipes(token);
	token = get_command(token, cmd_nbr);
	exec = handle_redirection(&token, env);
	if (!exec)
		exit(0);
	if (cmd_nbr != 0 && exec->in == -1)
		dup2(pipes[cmd_nbr - 1][0], 0);
	if (cmd_nbr < count && exec->out == -1)
		dup2(pipes[cmd_nbr][1], 1);
	close_pipes(pipes, count);
	if (exec_bultin(token, env) == 1)
		exec_command(exec);
	free_exec(exec);
	exit(0);
}

void	wait_all(int *pid, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		waitpid(pid[i], NULL, WUNTRACED);
		i++;
	}
	free(pid);
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

int	pipex(t_token *token, t_env *env, int count)
{
	int	**pipes;
	int	*pid;
	int	i;

	i = 0;
	pipes = setup_pipes(token);
	if (!pipes)
		return (1);
	pid = malloc(sizeof(int) * (count + 1));
	if (!pid)
		return (1);
	create_child(pid, count);
	while (i <= count)
	{
		if (pid[i] == 0)
			child_pipex(token, env, pipes, i);
		i++;
	}
	close_pipes(pipes, count);
	wait_all(pid, count);
	free_pipes(pipes);
	return (0);
}
