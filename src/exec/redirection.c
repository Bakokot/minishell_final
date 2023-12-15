/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:24:23 by yallo             #+#    #+#             */
/*   Updated: 2023/12/16 19:39:10 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_token(t_token **token_lst, size_t index)
{
	t_token	*tmp;
	t_token	*before;
	t_token	*current;

	tmp = *token_lst;
	while (index - 1 > 0 && tmp)
	{
		tmp = tmp->next;
		index--;
	}
	before = tmp;
	current = tmp->next;
	before->next = current->next->next;
	free(current->next->token);
	free(current->next);
	free(current->token);
	free(current);
}

static void	remove_redirection(t_token *head)
{
	size_t	index;
	t_token	*token_lst;

	index = 0;
	token_lst = head;
	while (token_lst && token_lst->type != 1)
	{
		if (token_lst->type != 0 && token_lst->type != 1)
		{
			unset_token(&head, index);
			token_lst = head;
			index = 0;
		}
		index++;
		token_lst = token_lst->next;
	}
}

static int	change_output(t_token *token_lst, t_exec **exec, int flags)
{
	int	file;

	file = open(token_lst->next->token, flags, 0777);
	if (!file)
	{
		ft_printf((*exec)->sstderr, "Error in open\n");
		return (1);
	}
	dup2(file, 1);
	(*exec)->out = file;
	return (0);
}

static int	change_input(t_token *token_lst, t_exec **exec, int flags)
{
	int	file;

	file = open(token_lst->next->token, flags, 0777);
	if (file == -1)
	{
		ft_printf((*exec)->sstderr, "No such file or directory: %s\n", token_lst->next->token);
		return (1);
	}
	dup2(file, 0);
	(*exec)->in = file;
	return (0);
}

int	change_standard_fd(t_token *token_lst, t_exec **exec, t_env *env)
{
	int	returns;
	t_token	*head;

	head = token_lst;
	returns = 0;
	while (token_lst && exec && token_lst->type != 1)
	{
		if (token_lst->type == 2)
			returns = change_input(token_lst, exec, O_RDONLY);
		if (token_lst->type == 3)
			returns = handle_heredoc(token_lst, *exec, env);
		if (token_lst->type == 4)
			returns = change_output(token_lst, exec, O_WRONLY | O_CREAT | O_TRUNC);
		if (token_lst->type == 5)
			returns = change_output(token_lst, exec, O_WRONLY | O_CREAT | O_APPEND);
		if (returns == 1)
			return (1);
		token_lst = token_lst->next;
	}
	remove_redirection(head);
	return (0);
}
