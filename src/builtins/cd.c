/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:56:31 by yallo             #+#    #+#             */
/*   Updated: 2023/11/30 12:19:06 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ajouter cd No arg --> cd $HOME

int	cd(t_token	*token_lst)
{
	token_lst = token_lst->next;
	if (chdir(token_lst->token) == -1)
	{
		printf("cd: %s: No such file or directory\n", token_lst->token);
		return (1);
	}
	return (0);
}
