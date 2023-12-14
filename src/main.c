/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:18 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/14 12:42:30 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

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

static char	*read_new_line(char *line)
{
	char	*new_line;
	char	*temp;

	temp = line;
	new_line = readline("> ");
	if (new_line == NULL)
	{
		write(1, ERR_EOF1, ft_strlen(ERR_EOF1));
		write(1, &line[0], 1);
		write(1, ERR_EOF2, ft_strlen(ERR_EOF2));
		free(line);
		return (NULL);	
	}
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
	t_env	*env;
	t_token	**token_lst;

	g_exit_status = 0;
	(void)argv;
	if (argc > 1)
		return (printf("./minishell takes no argument\n"), 0);
	env = init_env(envp);
	print_env(env);
	signal_handling();
	while (1)
	{
		token_lst = NULL;
		signal_handling();
		line = readline("minishell $>");
		if (line == NULL)
			ctrl_d_handler(line, token_lst, env);
		while (line != NULL && close_quotes(line) == false)
			line = read_new_line(line);
		if (line != NULL)
		{
			add_history(line);
			token_lst = tokenize(line, env);
			handle_command(*token_lst, env);
			free_all_token(token_lst);
			free(line);
		}
	}
	//rl_clear_history();
	//free_all_env ou free_all
}
