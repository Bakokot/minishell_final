/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:18 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/08 23:32:39 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	main(int argc, char **argv, char **envp)
int	main()
{
	char	*line;
	t_token	**token_lst;

	while (1)
	{
		line = readline("minishell $>");
		//add_history(line);
		token_lst = tokenize(line);
		free_all(token_lst);
		free(line);
		//rl_clear_history();
	}
}
