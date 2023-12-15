/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:22:01 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/16 19:46:22 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_env(t_env *env_lst)
{
	t_env	*temp;

	while (env_lst)
	{
		temp = env_lst->next;
		if (env_lst->key)
			free(env_lst->key);
		if (env_lst->values)
			free(env_lst->values);
		free(env_lst);
		env_lst = temp;
	}
}

void	free_all_token(t_token **token_lst)
{
	t_token	*temp;

	while (*token_lst)
	{
		temp = (*token_lst)->next;
		if ((*token_lst)->token)
			free((*token_lst)->token);
		free(*token_lst);
		*token_lst = temp;
	}
	free(token_lst);
}

void	free_all(t_token **token_lst, t_env *env)
{
	free_all_token(token_lst);
	free_all_env(env);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
