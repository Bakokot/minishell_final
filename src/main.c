/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:18 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/20 19:26:10 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

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
	t_env	*env;
	char	*line;
	t_token	**token;

	g_exit_status = 0;
	(void)argv;
	if (argc > 1)
		return (printf("./minishell takes no argument\n"), 0);
	env = init_env(envp);
	signal_handling();
	while (1)
	{
		token = NULL;
		signal_handling();
		line = readline("minishell $>");
		if (line == NULL)
			ctrl_d_handler(line, token, env);
		while (line != NULL && unclosed_quotes(line) == true)
			line = read_new_line(line);
		add_history(line);
		token = tokenize(line, env);
		handle_command(token, env);
		free_all_token(token);
		free(line);
	}
}
