/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/15 13:50:21 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_fd(t_exec *exec)
{
	dup2(exec->sstdin, 0);
	dup2(exec->sstdout, 1);
	dup2(exec->sstderr, 2);
}

void	handle_command(t_token **token_lst, t_env *env)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return ;
	if (init_exec(*token_lst, env, &exec))
	{
		free_exec(exec);
		return ;
	}
	if (exec_bultin(*token_lst, env))
		exec_command(exec);
	restore_fd(exec);
	free_exec(exec);
}
