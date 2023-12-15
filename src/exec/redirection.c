/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:24:23 by yallo             #+#    #+#             */
/*   Updated: 2023/12/14 14:53:10 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_token_redir(t_token **token_lst, size_t index)
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

void	remove_redirection(t_token *head)
{
	size_t	index;
	t_token	*token_lst;

	index = 0;
	token_lst = head;
	while (token_lst)
	{
		if (token_lst->type != 0 && token_lst->type != 1)
		{
			unset_token_redir(&head, index);
			token_lst = head;
			index = 0;
		}
		index++;
		token_lst = token_lst->next;
	}
}

void	change_output(t_token *token_lst, t_exec **exec, int flags)
{
	int	file;

	file = open(token_lst->next->token, flags, 0777);
	if (!file)
	{
		*exec = NULL;
		printf("Error in open\n");
		return ;
	}
	(*exec)->out = file;
	dup2(file, 1);
	dup2(file, 2);
}

void	change_input(t_token *token_lst, t_exec **exec, int flags)
{
	int	file;

	file = open(token_lst->next->token, flags, 0777);
	if (file == -1)
	{
		*exec = NULL;
		printf("No such file or directory\n");
		return ;
	}
	(*exec)->in = file;
	dup2(file, 0);
}

int	handle_redirection(t_token *token_lst, t_exec **exec)
{
	t_token	*head;

	head = token_lst;
	while (token_lst && exec && token_lst->type != 1)
	{
		if (token_lst->type == 4)
			change_output(token_lst, exec, O_WRONLY | O_CREAT | O_TRUNC);
		if (token_lst->type == 5)
			change_output(token_lst, exec, O_WRONLY | O_CREAT | O_APPEND);
		if (token_lst->type == 2)
			change_input(token_lst, exec, O_RDONLY);
		token_lst = token_lst->next;
	}
	if (!*exec)
		return (1);
	remove_redirection(head);
	return (0);
}
