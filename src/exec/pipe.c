/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:01:40 by yallo             #+#    #+#             */
/*   Updated: 2023/12/20 17:44:58 by yallo            ###   ########.fr       */
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
	restore_fd(exec);
	free_exec(exec);
	exit(0);
}

int	pipex(t_token *token, t_env *env, int count)
{
	int	**pipes;
	int	pid;
	int	i;

	i = 0;
	pipes = setup_pipes(token);
	if (!pipes)
		return (1);
	while (i <= count)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
			child_pipex(token, env, pipes, i);
		else
		{
			close_pipes(pipes, i - 1);
			waitpid(pid, NULL, WUNTRACED);
		}
		i++;
	}
	close_pipes(pipes, count);
	free_pipes(pipes);
	return (0);
}
