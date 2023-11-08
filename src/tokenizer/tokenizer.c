/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:56:19 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/08 23:19:59 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_quotes(char *line, int *i)
{
	int	quote;
	int	add_size;

	quote = is_quote(line[*i]);
	add_size = 0;
	if (quote != 0)
	{
		*i += 1;
		add_size++;
		while (line[*i] != quote && line[*i])
		{
			*i += 1;
			add_size++;
		}
	}
	return (add_size);
}

static void	add_metachar_token(t_token **token_lst, char *line, int *i)
{
	char	*str;
	int		type;

	type = line[*i];
	if (is_double_redirection(line + *i))
	{
		if (type == '>')
			type = ARO;
		else if (type == '<')
			type = HEREDOC;
		str = ft_strndup(line + *i, 2);
		add_back_token(token_lst, create_new_token(str, type));
		*i+=2;
	}
	else
	{
		if (type == '>')
			type = RO;
		else if (type == '<')
			type = RI;
		else if (type == '|')
			type = PIPE;
		str = ft_strndup(line + *i, 1);
		add_back_token(token_lst, create_new_token(str, type));
		*i+=2;
	}
}

static void	add_litteral_token(t_token **token_lst, char *line, int *i)
{
	char	*str;
	int		dup_size;
	int		temp_i;

	dup_size = 0;
	temp_i = *i;
	while (!is_metachar(line[*i]) && !isspace(line[*i]) && line[*i])
	{
		dup_size += skip_quotes(line, i);
		*i += 1;
		dup_size++;
	}
	str = ft_strndup(line +  temp_i, dup_size);
	add_back_token(token_lst, create_new_token(str, LITTERAL));
}

/**
 * DEBUG PRINTF TOKEN LST
*/
static void	print_token_lst(t_token *token_lst)
{
	printf("----- TOKEN LIST -----\n");
	while (token_lst)
	{
		printf("TOKEN == %s\n", token_lst->token);
		printf("TOKEN == %d\n", token_lst->type);
		printf("---------------------\n");
		token_lst = token_lst->next;
	}
}

void	delete_first_token(t_token **token_lst)
{
	t_token	*temp;

	temp = (*token_lst);
	(*token_lst) = (*token_lst)->next;
	free(temp);
}

t_token	**tokenize(char *line)
{
	t_token	**token_lst;
	int		i;

	token_lst = malloc(sizeof(t_token *));
	if (!token_lst)
		return(log_error(ERR_MALLOC), NULL);
	*token_lst = create_new_token("to delete", 0); 
	i = 0;
	while (line[i])
	{
		if (is_metachar(line[i]))
			add_metachar_token(token_lst, line, &i);
		else
			add_litteral_token(token_lst, line, &i);
		while (isspace(line[i]))
			i++;
	}
	delete_first_token(token_lst);
	print_token_lst(*token_lst);
	return (token_lst);
}
