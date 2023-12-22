/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:24:23 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 13:06:52 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_token(t_token **token_lst, int index)
{
	t_token	*tmp;
	t_token	*current;

	tmp = *token_lst;
	if (index == 0)
	{
		current = tmp;
		*token_lst = tmp->next->next;
	}
	else
	{
		while (index - 1 > 0 && tmp)
		{
			tmp = tmp->next;
			index--;
		}
		current = tmp->next;
		tmp->next = current->next->next;
	}
	free(current->next->token);
	free(current->next);
	free(current->token);
	free(current);
}

static int	change_output(t_token *token_lst, t_exec *exec, int flags)
{
	int	file;

	file = open(token_lst->next->token, flags, 0777);
	if (file == -1)
	{
		ft_printf(2, "Error in open\n");
		return (1);
	}
	dup2(file, 1);
	exec->out = file;
	return (0);
}

static int	change_input(t_token *token_lst, t_exec *exec, int flags)
{
	int	file;

	file = open(token_lst->next->token, flags, 0777);
	if (file == -1)
	{
		ft_printf(2, "No such file or directory: %s\n", token_lst->next->token);
		return (1);
	}
	dup2(file, 0);
	exec->in = file;
	return (0);
}

int	change_standard_fd(t_token *token_lst, t_exec *exec)
{
	int	i;
	int	returns;

	i = 0;
	returns = 0;
	while (token_lst)
	{
		if (token_lst->type == 2)
			returns = change_input(token_lst, exec, O_RDONLY);
		if (token_lst->type == 3)
		{
			dup2(exec->hd[i].fd_heredoc, 0);
			exec->in = exec->hd[i].fd_heredoc;
		}
		if (token_lst->type == 4)
			returns = change_output(token_lst, exec, O_WRONLY | O_CREAT | O_TRUNC);
		if (token_lst->type == 5)
			returns = change_output(token_lst, exec, O_WRONLY | O_CREAT | O_APPEND);
		if (token_lst->type == 1)
			i++;
		if (returns == 1)
			return (1);
		token_lst = token_lst->next;
	}
	return (0);
}

void	remove_redirection(t_token **head)
{
	int		index;
	t_token	*token_lst;

	index = 0;
	token_lst = *head;
	while (token_lst)
	{
		if (token_lst->type != 0 && token_lst->type != 1)
		{
			unset_token(head, index);
			token_lst = *head;
			index = 0;
		}
		else
		{
			index++;
			token_lst = token_lst->next;
		}
	}
}
