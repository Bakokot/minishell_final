/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:15:09 by yallo             #+#    #+#             */
/*   Updated: 2023/12/23 01:03:45 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_token *token_lst)
{
	int	option;

	option = 0;
	token_lst = token_lst->next;
	if (token_lst && ft_strcmp(token_lst->token, "-n") == 0)
	{
		option = 1;
		token_lst = token_lst->next;
	}
	while (token_lst != NULL && token_lst->type == 0)
	{
		if (token_lst->token)
			printf("%s", token_lst->token);
		if (token_lst->next)
			printf(" ");
		token_lst = token_lst->next;
	}
	if (option == 0)
		printf("\n");
	g_exit_status = 0;
	return (0);
}
