/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:49:33 by thibault          #+#    #+#             */
/*   Updated: 2023/12/21 12:14:12 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	strisnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_env *env, t_token **to_free, t_token **token)
{
	char	*str;
	ft_printf(1, "\nexit", 1);
	if ((*token)->next->token == NULL)
	{
		free_all(to_free, env);
		exit(0);
	}
	if ((*token)->next->token && !(*token)->next->next->token)
	{
		if (strisnum((*token)->next->token))
		{
			free_all(to_free, env);
			exit(ft_atoi((*token)->next->token));
		}
		str = ft_strdup((*token)->next->token);
		free_all(to_free, env);
		ft_printf(1, "bash: exit: %s: numeric argument required\n", str);
		free(str);
		exit(2);
	}
	if ((*token)->next->token && (*token)->next->next->token)
	{
		ft_printf(1, "bash: exit: too many arguments\n", (*token)->next->token);
		return ;
	}
}
