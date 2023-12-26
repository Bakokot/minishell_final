/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/26 19:02:04 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_directory(char *path)
{
	struct stat	file;

	if (stat(path, &file) == -1)
		return (NULL);
	if (access(path, F_OK) == 0)
	{
		if (S_ISDIR(file.st_mode))
		{
			ft_printf(2, "%s: Is a directory\n", path);
			g_exit_status = 126;
			return (NULL);
		}
		return (ft_strdup(path));
	}
	ft_printf(2, "%s: No such file or directory\n", path);
	g_exit_status = 127;
	return (NULL);
}

static char	*get_path(char *cmd, t_env *env)
{
	size_t	i;
	size_t	size;
	char	*path;
	char	**all_path;

	i = 0;
	all_path = ft_split(lookup_values("PATH", env), ':');
	while (all_path && all_path[i] && cmd != NULL)
	{
		size = ft_strlen(all_path[i]) + ft_strlen(cmd) + 2;
		path = malloc(sizeof(char) * size);
		if (!path)
			return (free_array(all_path), NULL);
		ft_strlcpy(path, all_path[i], size);
		ft_strlcat(path, "/", size);
		ft_strlcat(path, cmd, size);
		if (access(path, F_OK | X_OK) == 0)
			return (free_array(all_path), path);
		free(path);
		i++;
	}
	free_array(all_path);
	if (is_bultin(cmd) == 1)
		ft_printf(2, "%s : command not found\n", cmd);
	return (NULL);
}

t_exec	*fill_exec(t_exec *exec, t_token *token_lst, t_env *env, int i)
{
	exec->envp = env_lst_into_char(env);
	exec->args = token_lst_into_char(get_command(token_lst, i));
	if (!exec->args || exec->args[0] == NULL || !exec->envp)
		return (free_exec(exec, token_lst), NULL);
	if (ft_strchr(exec->args[0], '/') != NULL)
		exec->path = check_directory(exec->args[0]);
	else
	{
		exec->path = get_path(exec->args[0], env);
		if (!exec->path)
			g_exit_status = 127;
	}
	if (exec->path == NULL)
		return (free_exec(exec, token_lst), NULL);
	return (exec);
}

t_exec	*handle_redirection(t_token **token_lst, t_env *env, t_heredoc *hd, int i)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	init_exec(exec, hd);
	if (change_standard_fd(get_command(*token_lst, i), exec))
		return (free_exec(exec, *token_lst), NULL);
	remove_redirection(token_lst);
	if (*token_lst == NULL)
		return (free_exec(exec, *token_lst), NULL);
	exec = fill_exec(exec, *token_lst, env, i);
	return (exec);
}

int	execute(t_token **token, t_env *env, t_heredoc *hd)
{
	t_exec		*exec;

	exec = handle_redirection(token, env, hd, 0);
	if (exec == NULL || token == NULL)
		return (1);
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
	hd = check_heredocs(*token, env);
	if (hd)
	{
		signal_handling(IN_PROGRAM);
		if (count == 0)
			execute(token, env, hd);
		else
			pipex(token, env, count, hd);
		signal_handling(IN_SHELL);
	}
}
