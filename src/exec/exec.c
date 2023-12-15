/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:52:08 by yallo             #+#    #+#             */
/*   Updated: 2023/12/14 15:05:19 by yallo            ###   ########.fr       */
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
			return (free_array(all_path), path);
		free(path);
		i++;
	}
	return (NULL);
}

int	init_exec(t_token *token_lst, t_env *env, t_exec **exec)
{
	(*exec)->sstdin = dup(0);
	(*exec)->sstdout = dup(1);
	(*exec)->sstderr = dup(2);
	(*exec)->envp = NULL;
	(*exec)->args = NULL;
	(*exec)->path = NULL;
	if (handle_redirection(token_lst, exec))
		return (1);
	(*exec)->envp = env_lst_into_char(env);
	(*exec)->args = token_lst_into_char(token_lst);
	(*exec)->path = get_path(token_lst->token, env);
	if (!(*exec)->path && is_bultin(token_lst) == 1)
	{
		write((*exec)->sstderr, (*exec)->args[0], ft_strlen((*exec)->args[0]));
		write((*exec)->sstderr, ": command not found\n", 21);
		return (1);
	}
	return (0);
}

void	free_exec(t_exec *exec)
{
	if (exec->args != NULL)
		free_array(exec->args);
	if (exec->envp != NULL)
		free_array(exec->envp);
	if (exec->path != NULL)
		free(exec->path);
	free(exec);
}

void	exec_command(t_exec	*exec)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (execve(exec->path, exec->args, exec->envp) == -1)
		{
			write(exec->sstderr, exec->args[0], ft_strlen(exec->args[0]));
			write(exec->sstderr, ": command not found\n", 21);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
	}
}
