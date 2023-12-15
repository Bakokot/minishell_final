/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:17:00 by yallo             #+#    #+#             */
/*   Updated: 2023/12/14 12:31:04 by yallo            ###   ########.fr       */
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
	while (token_lst)
	{
		size = ft_strlen(token_lst->token) + 1;
		args[i] = malloc(sizeof(char) * size);
		if (!args[i])
			return (NULL);
		ft_strlcpy(args[i], token_lst->token, size);
		token_lst = token_lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
