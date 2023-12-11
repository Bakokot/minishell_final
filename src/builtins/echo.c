/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:15:09 by yallo             #+#    #+#             */
/*   Updated: 2023/12/11 14:03:18 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_token *token_lst)
{
	int	option;

	option = 0;
	token_lst = token_lst->next;
	if (ft_strcmp(token_lst->token, "-n") == 0)
	{
		option = 1;
		token_lst = token_lst->next;
	}
	while (token_lst != NULL && token_lst->type == 0)
	{
		printf("%s", token_lst->token);
		if (token_lst->next)
			printf(" ");
		token_lst = token_lst->next;
	}
	if (option == 0)
		printf("\n");
	return (0);
}
