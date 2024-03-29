/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:18 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/27 14:28:48 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static bool	no_history(char *line)
{
	int	i;

	i = 0;
	if (ft_strcmp(line, "") == 0)
		return (true);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}

static void	handle_line(char *line, t_token **token, t_env *env)
{
	if (no_history(line) == false)
		add_history(line);
	token = tokenize(line, env);
	free(line);
	if (token != NULL)
	{
		handle_command(token, env);
		free_all_token(token);
	}
}

static t_token	**init_loop(void)
{
	signal_handling(IN_SHELL);
	return (NULL);
}

static t_env	*init_mini(char **envp)
{
	g_exit_status = 0;
	return (init_env(envp));
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
	env = init_mini(envp);
	while (1)
	{
		token = init_loop();
		line = readline("minishell $>");
		if (line == NULL)
			ctrl_d_handler(line, token, env);
		while (line != NULL && (unclosed_quotes(line) == true \
		|| unclosed_pipe(line) == true))
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
