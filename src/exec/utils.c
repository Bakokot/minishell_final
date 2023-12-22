/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:17:00 by yallo             #+#    #+#             */
/*   Updated: 2023/12/22 15:32:03 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_lst_into_char(t_token *token_lst)
{
	size_t	i;
	size_t	size;
	char	**args;

	size = token_size(token_lst);
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (token_lst && token_lst->type != 1)
	{
		if (token_lst->empty == false)
		{
			size = ft_strlen(token_lst->token) + 1;
			args[i] = malloc(sizeof(char) * size);
			if (!args[i])
				return (free_array(args), NULL);
			ft_strlcpy(args[i], token_lst->token, size);
			i++;
		}
		token_lst = token_lst->next;
	}
	args[i] = NULL;
	return (args);
}
