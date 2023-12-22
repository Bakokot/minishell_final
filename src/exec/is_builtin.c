/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:03:07 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 16:17:42 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_bultin(char *cmd, char *to_check)
{
	if (ft_strlen(to_check) == ft_strlen(to_check))
		if (!ft_strncmp(cmd, to_check, 2))
			return (1);
	return (0);
}

int	is_bultin(t_token *token_lst)
{
	if (check_bultin("cd", token_lst->token))
		return (0);
	if (check_bultin("echo", token_lst->token))
		return (0);
	if (check_bultin("env", token_lst->token))
		return (0);
	if (check_bultin("export", token_lst->token))
		return (0);
	if (check_bultin("pwd", token_lst->token))
		return (0);
	if (check_bultin("unset", token_lst->token))
		return (0);
	if (check_bultin("exit", token_lst->token))
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
