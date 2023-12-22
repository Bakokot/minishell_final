/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 08:40:35 by thibault          #+#    #+#             */
/*   Updated: 2023/12/22 21:56:37 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * exit when we receive end of file
*/
void	ctrl_d_handler(char *line, t_token **token_lst, t_env *env)
{
	if (line)
		free(line);
	if (token_lst)
		free_all_token(token_lst);
	if (env)
		free_all_env(env);
	write(1, "exit\n", 5);
	exit(translate_error(g_exit_status));
}
