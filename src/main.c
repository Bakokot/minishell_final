/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:18 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/26 19:57:18 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;



static char	*read_new_line_pipe(char *line)
{
	char	*new_line;
	char	*temp;

	temp = line;
	new_line = readline("> ");
	if (new_line == NULL)
	{
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

static char	*read_new_line(char *line)
{
	char	*new_line;
	char	*temp;
	char	c;

	c = 0;
	temp = line;
	new_line = readline("> ");
	if (new_line == NULL)
	{
		c = strchr_quote(line);
		write(1, ERR_EOF1, ft_strlen(ERR_EOF1));
		write(1, &c, 1);
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

static void	handle_line(char *line, t_token **token, t_env *env)
{
	if (ft_strcmp(line, "") != 0)
		add_history(line);
	token = tokenize(line, env);
	free(line);
	handle_command(token, env);
	free_all_token(token);
}

static t_token	**init_loop(void)
{
	signal_handling(IN_SHELL);
	return (NULL);
}

/**
 * EXPLANATION :
	--> line == NULL when we ctrl + D // EOF !
	--> so we exit when we do ctrl + D
*/
int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*line;
	t_token	**token;

	(void)argv;
	if (argc > 1)
		return (ft_printf(2, "./minishell takes no argument\n"), 0);
	g_exit_status = 0;
	env = init_env(envp);
	while (1)
	{
		token = init_loop();
		line = readline("minishell $>");
		if (line == NULL)
			ctrl_d_handler(line, token, env);
		while (line != NULL && (unclosed_quotes(line) == true || unclosed_pipe(line) == true))
		{
			if (unclosed_quotes(line) == true)
				line = read_new_line(line);
			else
				line = read_new_line_pipe(line);
		}
		if (line != NULL)
			handle_line(line, token, env);
	}
}
