/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:18:08 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 22:34:49 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_env *env)
{
	while (env)
	{
		printf("%s=", env->key);
		if (env->values)
			printf("%s", env->values);
		printf("\n");
		env = env->next;
	}
	g_exit_status = 0;
	return (0);
}
