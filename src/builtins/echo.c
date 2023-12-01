/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:15:09 by yallo             #+#    #+#             */
/*   Updated: 2023/11/30 11:54:27 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo -n --> int option != 0
int	echo(t_token *token_lst, int option)
{
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
