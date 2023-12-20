/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:27:57 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/20 19:23:12 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	closed_quotes_nbr(char *str)
{
	int	i;
	int	quote_type;
	int	ret;

	i = 0;
	quote_type = 0;
	ret = 0;
	while (str[i])
	{
		quote_type = is_quote(str[i]);
		if (quote_type != 0)
		{
			i++;
			while (str[i] != quote_type && str[i])
				i++;
			if (str[i])
				ret += 2;
		}
		i++;
	}
	return (ret);
}

static void	init_var(int *i, int *j, int *flag)
{
	*i = 0;
	*j = 0;
	*flag = 0;
}

static char	*strdup_erase_closed_quotes(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		flag;

	init_var(&i, &j, &flag);
	ret = malloc(ft_strlen(str) - closed_quotes_nbr(str) + 1);
	while (str[i])
	{
		if (flag == 0 && is_quote(str[i]) != 0)
		{
			printf("entered quote == \t%c\n", str[i]);
			flag = str[i++];
			//i++;
		}
		if (str[i] == flag)
		{
			printf("entered end quote == \t%c\n", str[i]);
			flag = 0;
			i++;
		}
		else if (str[i] != flag)
		{
			printf("entered copy char == \t%c\n", str[i]);
			ret[j++] = str[i++];
			//j++;
			//i++;
		}
	}
	ret[j] = 0;
	printf("%s\n", ret);
	return (ret);
}

/**
 * Remove the quotes from the tokens so the exec can run smoothly
*/
void	remove_token_quotes(t_token **token_lst)
{
	t_token	*cpy;
	char	*temp;

	cpy = *token_lst;
	while (cpy)
	{
		if (closed_quotes(cpy->token) == true)
		{
			printf("ici\n");
			temp = cpy->token;
			cpy->quoted = true;
			cpy->token = strdup_erase_closed_quotes(cpy->token);
			free(temp);
		}
		cpy = cpy->next;
	}
}
