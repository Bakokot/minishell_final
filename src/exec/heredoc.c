/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:31:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/20 11:18:28 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_heredoc(t_token **heredoc, t_exec *exec, t_env *env)
{
	t_token *head;

	head = *heredoc;
	exec->fd_heredoc = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (exec->fd_heredoc == -1)
		return (free_all_token(heredoc), 1);
	//replace_vars(heredoc, env);
	(void)env;
	while (head)
	{
		if (head->token == NULL)
			ft_printf(exec->fd_heredoc, "\n");
		else
			ft_printf(exec->fd_heredoc, "%s\n", head->token);
		head = head->next;
	}
	ft_printf(exec->fd_heredoc, "\0");
	close(exec->fd_heredoc);
	exec->fd_heredoc = open("heredoc", O_RDONLY, 0777);
	if (exec->fd_heredoc == -1)
		return (free_all_token(heredoc), 1);
	dup2(exec->fd_heredoc, 0);
	exec->in = exec->fd_heredoc;
	return (0);
}

int	handle_heredoc(t_token *token, t_exec *exec, t_env *env)
{
	t_token	*new;
	t_token	**heredoc;
	char	*line;
	char	*delimiter;

	heredoc = malloc(sizeof(t_token *));
	if (!heredoc)
		return (1);
	*heredoc = NULL;
	delimiter = token->next->token;
	while (1)
	{
		line = readline("heredoc>");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) && ft_strlen(delimiter) == ft_strlen(line))
			break ;
		new = create_new_token(line, 0);
		if (!new)
			return (free_all_token(heredoc), 1);
		add_back_token(heredoc, new);
	}
	free(line);
	if (write_heredoc(heredoc, exec, env) == 1)
		return (1);
	free_all_token(heredoc);
	return (0);
}
