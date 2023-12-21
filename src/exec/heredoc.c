/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:31:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/21 11:49:22 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**setup_heredoc(t_exec *exec)
{
	t_token	**heredoc;

	heredoc = NULL;
	unlink("heredoc");
	dup2(exec->sstdin, 0);
	heredoc = malloc(sizeof(t_token *));
	if (!heredoc)
		return (NULL);
	*heredoc = NULL;
	return (heredoc);
}

int	write_heredoc(t_token **heredoc, t_exec *exec)
{
	t_token *head;

	head = *heredoc;
	exec->fd_heredoc = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (exec->fd_heredoc == -1)
		return (free_all_token(heredoc), 1);
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
	free_all_token(heredoc);
	return (0);
}

int	end_heredoc(t_token *token, char *line)
{
	char	*delimiter;

	delimiter = token->next->token;
	if (line == NULL)
	{
		ft_printf(2, "Warning: heredoc delimiter was %s\n", delimiter);
		return (1);
	}
	if (ft_strlen(delimiter) == ft_strlen(line))
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			return (1);
	return (0);
}

int	handle_heredoc(t_token *token, t_exec *exec, t_env *env)
{
	char	*line;
	t_token	*new;
	t_token	**heredoc;

	heredoc = setup_heredoc(exec);
	if (!heredoc)
		return (1);
	while (1)
	{
		line = readline("heredoc>");
		if (line == NULL)
			break ;
		if (end_heredoc(token, line))
			break ;
		new = create_new_token(line, 0);
		if (!new)
			return (free_all_token(heredoc), 1);
		add_back_token(heredoc, new);
	}
	free(line);
	if (token->next->quoted == false)
		replace_varsn(heredoc, env);
	if (write_heredoc(heredoc, exec) == 1)
		return (1);
	return (0);
}
