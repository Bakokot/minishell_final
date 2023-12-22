/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:49:33 by thibault          #+#    #+#             */
/*   Updated: 2023/12/22 11:26:40 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	strisnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_env *env, t_token **token, t_exec *exec)
{
	int		exit_status;

	exit_status = 2;
	ft_printf(1, "exit\n", 1);
	if ((*token)->next == NULL)
	{
		free_exec(exec, *token);
		free_all(token, env);
		exit(g_exit_status);
	}
	else
	{
		if (strisnum((*token)->next->token))
		{
			if ((*token)->next->next != NULL)
				return (ft_printf(1, "exit: too many arguments\n", (*token)->next->token), 1);
			exit_status = ft_atoi((*token)->next->token);
		}
		else
			ft_printf(1, "exit: %s: numeric argument required\n", (*token)->next->token);
		free_exec(exec, *token);
		free_all(token, env);
		exit(exit_status);
	}
	return (0);
}
