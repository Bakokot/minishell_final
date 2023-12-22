/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:31:24 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 14:26:26 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**setup_heredoc(t_heredoc *hd, int nbr_cmd)
{
	t_token	**heredoc;

	heredoc = NULL;
	if (hd[nbr_cmd].fd_heredoc != -1)
		unlink(hd[nbr_cmd].heredoc);
	heredoc = malloc(sizeof(t_token));
	if (!heredoc)
		return (NULL);
	*heredoc = NULL;
	return (heredoc);
}

int	write_heredoc(t_token **heredoc, t_heredoc *hd, int nbr_cmd)
{
	t_token *head;

	head = *heredoc;
	hd[nbr_cmd].fd_heredoc = open(hd[nbr_cmd].heredoc, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (hd[nbr_cmd].fd_heredoc == -1)
		return (free_all_token(heredoc), 1);
	while (head)
	{
		if (head->token == NULL)
			ft_printf(hd[nbr_cmd].fd_heredoc, "\n");
		else
			ft_printf(hd[nbr_cmd].fd_heredoc, "%s\n", head->token);
		head = head->next;
	}
	ft_printf(hd[nbr_cmd].fd_heredoc, "\0");
	close(hd[nbr_cmd].fd_heredoc);
	hd[nbr_cmd].fd_heredoc = open(hd[nbr_cmd].heredoc, O_RDONLY, 0777);
	if (hd[nbr_cmd].fd_heredoc == -1)
		return (free_all_token(heredoc), 1);
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

int	handle_heredoc(t_token *token, t_heredoc *hd, t_env *env, int nbr_cmd)
{
	char	*line;
	t_token	*new;
	t_token	**heredoc;

	heredoc = setup_heredoc(hd, nbr_cmd);
	if (!heredoc)
		return (1);
	while (1)
	{
		line = readline("heredoc>");
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
	if (write_heredoc(heredoc, hd, nbr_cmd) == 1)
		return (1);
	return (0);
}

void	set_heredoc(t_heredoc *heredoc, int size)
{
	int		i;
	int		add;
	char	*name;

	i = 0;
	add = 0;
	while (i < size)
	{
		name = ft_itoa(i + add);
		if (access(name, F_OK) == 0)
		{
			free(name);
			add++;
		}
		else
		{
			heredoc[i].heredoc = name;
			heredoc[i].fd_heredoc = -1;
			if (!heredoc[i].heredoc)
				return ;
			i++;
		}
	}
}

t_heredoc	*check_heredocs(t_token	*token, t_env *env)
{
	int			i;
	int			size;
	t_heredoc	*hd;

	size = count_pipes(token) + 1;
	hd = malloc(sizeof(t_heredoc) * size);
	if (!hd)
		return (NULL);
	set_heredoc(hd, size);
	i = 0;
	size = 0;
	while (token)
	{
		if (token->type == 3)
			size = handle_heredoc(token, hd, env, i);
		if (token->type == 1)
			i++;
		if (size != 0)
			return (NULL);
		token = token->next;
	}
	return (hd);
}
