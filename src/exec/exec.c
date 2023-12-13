/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:52:08 by yallo             #+#    #+#             */
/*   Updated: 2023/12/13 16:01:17 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
