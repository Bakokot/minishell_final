/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:06:20 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 16:10:19 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_pipes(t_token *token)
{
	size_t	count;

	count = 0;
	while (token)
	{
		if (token->type == 1)
			count ++;
		token = token->next;
	}
	return (count);
}

int	**setup_pipes(t_token *token)
{
	int		**pipes;
	size_t	i;
	size_t	count;

	count = count_pipes(token);
	if (count == 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * (count + 1));
	if (!pipes)
		return (NULL);
	pipes[count] = NULL;
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (free_pipes(pipes), NULL);
		if (pipe(pipes[i]) == -1)
			return (free_pipes(pipes), NULL);
		i++;
	}
	return (pipes);
}

void	close_pipes(int **pipes, int limiter)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		if (limiter != -1 && i == limiter)
			return ;
		i++;
	}
}

void	free_pipes(int **pipes)
{
	size_t	i;

	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

t_token	*get_command(t_token *token, int index)
{
	int	i;

	i = 0;
	while (token)
	{
		if (index == 0)
			return (token);
		if (token->type == 1)
			i++;
		if (i == index)
			return (token->next);
		token = token-> next;
	}
	return (NULL);
}
