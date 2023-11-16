/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:18 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/16 23:59:50 by tbarde-c         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	**token_lst;
	t_env	*env;

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
		line = readline("minishell $>");
		add_history(line);
		token_lst = tokenize(line, env);
		free_all_token(token_lst);
		free(line);
	}
	//rl_clear_history();
	//free_all_env ou free_all
}
