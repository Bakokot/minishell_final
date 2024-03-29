/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:03:07 by yallo             #+#    #+#             */
/*   Updated: 2023/12/25 21:52:44 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_bultin(char *cmd, char *to_check)
{
	size_t	i;

	i = ft_strlen(cmd);
	if (ft_strlen(to_check) == i)
		if (!ft_strncmp(cmd, to_check, i))
			return (1);
	return (0);
}

int	is_bultin(char *cmd)
{
	if (check_bultin("cd", cmd))
		return (0);
	if (check_bultin("echo", cmd))
		return (0);
	if (check_bultin("env", cmd))
		return (0);
	if (check_bultin("export", cmd))
		return (0);
	if (check_bultin("pwd", cmd))
		return (0);
	if (check_bultin("unset", cmd))
		return (0);
	if (check_bultin("exit", cmd))
		return (0);
	return (1);
}

int	exec_bultin(t_token *token_lst, t_env *env)
{
	if (check_bultin("cd", token_lst->token))
		return (cd(token_lst, env), 0);
	if (check_bultin("echo", token_lst->token))
		return (echo(token_lst), 0);
	if (check_bultin("env", token_lst->token))
		return (env_builtin(env), 0);
	if (check_bultin("export", token_lst->token))
		return (export(token_lst, &env), 0);
	if (check_bultin("pwd", token_lst->token))
		return (pwd(), 0);
	if (check_bultin("unset", token_lst->token))
		return (unset(token_lst, &env), 0);
	if (check_bultin("exit", token_lst->token))
		return (0);
	return (1);
}

int	exec_exit(t_token **token, t_env *env, t_exec *exec)
{
	if (check_bultin("exit", (*token)->token))
	{
		ft_exit(env, token, exec);
		return (1);
	}
	return (0);
}
