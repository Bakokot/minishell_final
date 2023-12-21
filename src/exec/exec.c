/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:52:08 by yallo             #+#    #+#             */
/*   Updated: 2023/12/21 11:40:13 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(t_exec *exec)
{
	exec->sstdin = dup(0);
	exec->sstdout = dup(1);
	exec->fd_heredoc = -1;
	exec->in = -1;
	exec->out = -1;
	exec->envp = NULL;
	exec->args = NULL;
	exec->path = NULL;
}

void	free_exec(t_exec *exec)
{
	restore_fd(exec);
	if (exec->args != NULL)
		free_array(exec->args);
	if (exec->envp != NULL)
		free_array(exec->envp);
	if (exec->path != NULL)
		free(exec->path);
	free(exec);
}

void	restore_fd(t_exec *exec)
{
	if (exec->fd_heredoc != -1)
	{
		close(exec->fd_heredoc);
		unlink("heredoc");
	}
	dup2(exec->sstdin, 0);
	dup2(exec->sstdout, 1);
	close(exec->sstdin);
	close(exec->sstdout);
}

void	exec_command(t_exec	*exec)
{
	int		pid;
	int		status;

	status = -1;
	pid = fork();
	g_exit_status = 0;
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (execve(exec->path, exec->args, exec->envp) == -1)
		{
			ft_printf(2, "%s : command not found\n", exec->args[0]);
			exit(2);
		}
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (status != 0)
			g_exit_status = 127;
	}
}
