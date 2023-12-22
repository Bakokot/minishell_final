/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:56:19 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/22 17:42:33 by yallo            ###   ########.fr       */
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
		*i += 2;
	}
	else
	{
		str = ft_strndup(line + *i, 1);
		*i += 1;
		if (type == '>')
			add_back_token(token_lst, create_new_token(str, RO));
		else if (type == '<')
			add_back_token(token_lst, create_new_token(str, RI));
		else if (type == '|')
			add_back_token(token_lst, create_new_token(str, PIPE));
	}
}

static void	add_litteral_token(t_token **token_lst, char *line, int *i)
{
	char	*str;
	int		dup_size;
	int		temp_i;

	dup_size = 0;
	temp_i = *i;
	while (!is_metachar(line[*i]) && !ft_isspace(line[*i]) && line[*i])
	{
		dup_size += skip_quotes(line, i);
		*i += 1;
		dup_size++;
	}
	str = ft_strndup(line + temp_i, dup_size);
	add_back_token(token_lst, create_new_token(str, LITTERAL));
}

/**
 * loop for the function t_token	**tokenize(char *line, t_env *env)
 * it fills the tokens, wether they are litteral or metachar ones
*/
static void	tokenize_loop(int *i, char *line, t_token **token_lst)
{
	while (line[*i])
	{
		while (ft_isspace(line[*i]))
			*i += 1;
		if (is_metachar(line[*i]))
			add_metachar_token(token_lst, line, i);
		else if (!ft_isspace(line[*i]) && line[*i])
			add_litteral_token(token_lst, line, i);
		while (ft_isspace(line[*i]))
			*i += 1;
	}
}

t_token	**tokenize(char *line, t_env *env)
{
	t_token	**token_lst;
	int		i;

	token_lst = malloc(sizeof(t_token *));
	if (!token_lst)
		return (log_error(ERR_MALLOC), NULL);
	*token_lst = create_new_token("to delete", 0);
	i = 0;
	if (line != NULL)
		tokenize_loop(&i, line, token_lst);
	delete_first_token(token_lst);
	replace_varsn(token_lst, env);
	remove_token_quotes(token_lst);
	return (token_lst);
}
