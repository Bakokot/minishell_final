/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:56:19 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/08 18:40:26 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote();



void	add_metachar_token(t_token **token_lst, char *line, int *i)
{
	char	*str;

	if (is_double_redirection(line + *i))
	{
		str = ft_strndup(line + *i, 2);
		add_back_token(token_lst, create_new_token(str));
		*i+=2;
		//malloc new string size 2
		//add back new token
		//*i+=2
	}
}

t_token	**tokenize(char *line)
{
	t_token	**token_lst;
	int		i;

	token_lst = malloc(sizeof(t_token *));
	i = 0;
	while (line[i])
	{
		if (is_metachar(line[i]))
			add_metachar_token(token_lst, line, &i);
		/*else
			add_litteral_token();*/
	}
	return (token_lst);
}
