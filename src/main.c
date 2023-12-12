/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:18 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/12 13:15:57 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(t_env *env)
{
	while (env)
	{
		printf("------------\n");
		printf("KEY --> %s\n", env->key);
		if (env->values)
			printf("	VALUE --> %s\n", env->values);
		env = env->next;
	}
}

static bool close_quotes(char *line)
{
	int	i;
	int	quote_type;

	i = 0;
	while (line[i])
	{
		quote_type = is_quote(line[i]);
		i++;
		while (quote_type != 0 && line[i])
		{
			if (quote_type == line[i])
				quote_type = 0;
			i++;
		}
	}
	if (quote_type == 0)
		return (true);
	return (false);
}

static char	*read_new_line(char *line)
{
	char	*new_line;
	char	*temp;
	
	temp = line;
	new_line = readline("> ");
	line = ft_strjoin(line, "\n");
	free(temp);
	temp = line;
	line = ft_strjoin(line, new_line);
	free(temp);
	return (line);
}

/**
 * EXPLANATION : 
 * if (line == NULL)
		exit(0);
	--> line == NULL when we ctrl + D // EOF !
	--> so we exit when we do ctrl + D
*/
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	**token_lst;
	t_env	*env;

	//global = 0;
	(void)argc;
	(void)argv;
	/*int	i;
	i = 0;
	printf("----- ENV IS -----");
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}*/
	env = init_env(envp);
	print_env(env);
	while (1)
	{
		signal_handling();
		line = readline("minishell $>");
		if (line == NULL)
			ctrl_d_handler();
		while (close_quotes(line) == false)
			line = read_new_line(line);
		printf("the line we entered is : %s\n", line);
		add_history(line);
		token_lst = tokenize(line, env);
		free_all_token(token_lst);
		free(line);
	}
	//rl_clear_history();
	//free_all_env ou free_all
}
