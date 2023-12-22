/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:52:08 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 15:38:55 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(t_exec *exec, t_heredoc *hd)
{
	exec->hd = hd;
	exec->sstdin = dup(0);
	exec->sstdout = dup(1);
	exec->fd_heredoc = -1;
	exec->in = -1;
	exec->out = -1;
	exec->envp = NULL;
	exec->args = NULL;
	exec->path = NULL;
}

void	free_exec(t_exec *exec, t_token *token)
{
	if (exec == NULL)
		return ;
	restore_fd(exec, token);
	if (exec->args != NULL)
		free_array(exec->args);
	if (exec->envp != NULL)
		free_array(exec->envp);
	if (exec->path != NULL)
		free(exec->path);
	free(exec);
}

void	restore_fd(t_exec *exec, t_token *token)
{
	int	i;
	int	size;

	i = 0;
	size = count_pipes(token);
	while (i <= size)
	{
		if (exec->hd[i].fd_heredoc != -1)
		{
			close(exec->hd[i].fd_heredoc);
			unlink(exec->hd[i].heredoc);
		}
		free(exec->hd[i].heredoc);
		i++;
	}
	free(exec->hd);
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
