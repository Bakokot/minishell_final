/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:52:08 by yallo             #+#    #+#             */
/*   Updated: 2023/12/12 23:11:34 by yallo            ###   ########.fr       */
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
			printf("%s: command not found\n", exec->args[0]);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
	}
}
