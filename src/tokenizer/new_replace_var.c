/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_replace_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:49:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/15 14:59:13 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*double_quote_behaviour()
{
	
}

static void	update_var(t_token *token, t_env *env)
{
	int	flag_quote;
	int	i;

	i = 0;
	flag_quote = 0;
	flag_quote = is_quote(token->token[i]);
	while (token->token[i])
	{
		flag_quote = is_quote(token->token[i]);
		if (flag_quote == '\"')
		{
			double_quote_behaviour();
			flag_quote = 0;
		}
		/*else if (flag_quote == '\'')
		{

		}
		else
		{

		}*/
	}

}

void	replace_vars(t_token **token_lst, t_env *env)
{
	t_token	*token;

	token = (*token_lst);
	while (token)
	{
		update_var(token, env);
		token = token->next;
	}
}