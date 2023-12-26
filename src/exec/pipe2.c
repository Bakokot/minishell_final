/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:16:41 by thibault          #+#    #+#             */
/*   Updated: 2023/12/27 00:16:56 by thibault         ###   ########.fr       */
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
