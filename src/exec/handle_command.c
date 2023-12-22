/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 14:24:42 by yallo            ###   ########.fr       */
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
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	all_path = ft_split(lookup_values("PATH", env), ':');
	while (all_path && all_path[i])
	{
		size = ft_strlen(all_path[i]) + ft_strlen(cmd) + 2;
		path = malloc(sizeof(char) * size);
		if (!path)
			return (free_array(all_path), NULL);
		ft_strlcpy(path, all_path[i], size);
		ft_strlcat(path, "/", size);
		ft_strlcat(path, cmd, size);
		if (access(path, F_OK | X_OK) >= 0)
			return (free_array(all_path), path);
		free(path);
		i++;
	}
	free_array(all_path);
	return (NULL);
}

t_exec	*handle_redirection(t_token **token_lst, t_env *env, t_heredoc *hd)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	init_exec(exec, hd);
	if (change_standard_fd(*token_lst, exec))
		return (free_exec(exec, *token_lst), NULL);
	remove_redirection(token_lst);
	if (*token_lst == NULL)
		return(free_exec(exec, *token_lst), NULL);
	exec->envp = env_lst_into_char(env);
	exec->args = token_lst_into_char(*token_lst);
	if (!exec->args || !exec->envp)
		return (free_exec(exec, *token_lst), NULL);
	exec->path = get_path((*token_lst)->token, env);
	if (exec->path == NULL && is_bultin(*token_lst) == 1)
	{
		g_exit_status = 127;
		ft_printf(2, "%s : command not found\n", (*token_lst)->token);
		return (free_exec(exec, *token_lst), NULL);
	}
	return (exec);
}

int	execute(t_token **token, t_env *env, t_heredoc *hd)
{
	t_exec		*exec;

	exec = handle_redirection(token, env, hd);
	if (token == NULL)
	{
		g_exit_status = 0;
		return (1);
	}
	if (exec == NULL)
	{
		g_exit_status = 127;
		return (1);
	}
	if (exec_exit(token, env, exec) == 1)
	{
		g_exit_status = 1;
		free_exec(exec, *token);
		return (0);
	}
	if (exec_bultin(*token, env) == 1)
		exec_command(exec);
	free_exec(exec, *token);
	return (0);
}

void	handle_command(t_token **token, t_env *env)
{
	int			count;
	t_heredoc	*hd;

	if (check_args(*token) == 1)
		return ;
	count = count_pipes(*token);
	signal_handling(IN_PROGRAM);
	hd = check_heredocs(*token, env);
	if (hd)
	{
		if (count == 0)
			execute(token, env, hd);
		else
		{
			pipex(token, env, count, hd);
			free(hd);
		}
	}
	signal_handling(IN_SHELL);
}
