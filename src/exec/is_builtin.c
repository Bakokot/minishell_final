/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:03:07 by yallo             #+#    #+#             */
/*   Updated: 2023/12/09 14:03:34 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bultin(t_token *token_lst, t_env *env)
{
	if (!ft_strncmp("cd", token_lst->token, 2) && ft_strlen(token_lst->token) == 2)
		return (cd(token_lst, env), 0);
	if (!ft_strncmp("echo", token_lst->token, 4) && ft_strlen(token_lst->token) == 4)
		return (echo(token_lst), 0);
	if (!ft_strncmp("env", token_lst->token, 3) && ft_strlen(token_lst->token) == 3)
		return (env_builtin(env), 0);
	if (!ft_strncmp("export", token_lst->token, 6) && ft_strlen(token_lst->token) == 6)
		return (export(token_lst, &env), 0);
	if (!ft_strncmp("pwd", token_lst->token, 3) && ft_strlen(token_lst->token) == 3)
		return (pwd(), 0);
	if (!ft_strncmp("unset", token_lst->token, 5) && ft_strlen(token_lst->token) == 5)
		return (unset(token_lst, &env), 0);
	return (1);
}
