/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:18 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/25 18:27:28 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static char	strchr_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\"' && line[i] != '\'')
		i++;
	return (line[i]);
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
		token = NULL;
		signal_handling(IN_SHELL);
		line = readline("minishell $>");
		if (line == NULL)
			ctrl_d_handler(line, token, env);
		while (line != NULL && unclosed_quotes(line) == true)
			line = read_new_line(line);
		if (line != NULL)
			handle_line(line, token, env);
	}
}
