/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/12 23:16:00 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *cmd, t_env *env)
{
	size_t	i;
	size_t	size;
	char	*path;
	char	**all_path;

	i = 0;
	all_path = ft_split(lookup_values("PATH", env), ':');
	while (all_path[i])
	{
		size = ft_strlen(all_path[i]) + ft_strlen(cmd) + 2;
		path = malloc(sizeof(char) * size);
		if (!path)
			return (NULL);
		ft_strlcpy(path, all_path[i], size);
		ft_strlcat(path, "/", size);
		ft_strlcat(path, cmd, size);
		if (access(path, F_OK | X_OK) >= 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	init_exec(t_token *token_lst, t_env *env, t_exec *exec)
{
	exec->sstdin = dup(0);
	exec->sstdout = dup(1);
	exec->sstderr = dup(2);
	handle_redirection(token_lst, exec);
	if (!exec)
	{
		free(exec);
		return ;
	}
	exec->envp = env_lst_into_char(env);
	exec->args = token_lst_into_char(token_lst);
	exec->path = get_path(token_lst->token, env);
}

void	restore_fd(t_exec *exec)
{
	dup2(exec->sstdin, 0);
	dup2(exec->sstdout, 1);
	dup2(exec->sstderr, 2);
	free(exec);
}

void	handle_command(t_token *token_lst, t_env *env)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return ;
	init_exec(token_lst, env, exec);
	if (!exec)
		return ;
	if (is_bultin(token_lst, env) == 1)
		exec_command(exec);
	restore_fd(exec);
}
