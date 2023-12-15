/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:52:08 by yallo             #+#    #+#             */
/*   Updated: 2023/12/16 18:55:03 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_exec(t_exec *exec)
{
	exec->sstdin = dup(0);
	exec->sstdout = dup(1);
	exec->sstderr = dup(2);
	exec->fd_heredoc = -1;
	exec->envp = NULL;
	exec->args = NULL;
	exec->path = NULL;
	return (0);
}

void	free_exec(t_exec *exec)
{
	if (exec->args != NULL)
		free_array(exec->args);
	if (exec->envp != NULL)
		free_array(exec->envp);
	if (exec->path != NULL)
		free(exec->path);
	free(exec);
}

void	exec_command(t_exec	*exec)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (execve(exec->path, exec->args, exec->envp) == -1)
		{
			write(exec->sstderr, exec->args[0], ft_strlen(exec->args[0]));
			write(exec->sstderr, ": command not found\n", 21);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
	}
}
