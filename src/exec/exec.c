/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:52:08 by yallo             #+#    #+#             */
/*   Updated: 2023/12/11 14:08:30 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**token_lst_into_char(t_token *token_lst)
{
	size_t	i;
	size_t	size;
	char	**args;

	size = token_size(token_lst);
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (token_lst)
	{
		size = ft_strlen(token_lst->token) + 1;
		args[i] = malloc(sizeof(char) * size);
		if (!args[i])
			return (printf("Not good\n"), NULL);
		ft_strlcpy(args[i], token_lst->token, size);
		token_lst = token_lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

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

static void	exec_in_child(t_token *token_lst, t_env *env)
{
	char	*path;
	char	**args;
	char	**envp;

	envp = env_lst_into_char(env);
	args = token_lst_into_char(token_lst);
	path = get_path(token_lst->token, env);
	if (!path || execve(path, args, envp) == -1)
		printf("%s: command not found\n", token_lst->token);
	free_array(args);
	free_array(envp);
	free(path);
}

void	exec_command(t_token *token_lst, t_env *env)
{
	int		pid;

	if (is_bultin(token_lst, env) == 1)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			exec_in_child(token_lst, env);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			kill(pid, SIGTERM);
		}
	}
}
