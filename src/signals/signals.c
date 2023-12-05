/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:12:08 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/05 13:51:40 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_prompt(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ctrl_c_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	new_prompt();
}

/**
 * [Ctrl + \]	SIGQUIT --> ignored
 * [CTRL + C]	SIGINT --> print ^C and make a new prompt
 * [CTRL + D]	End Of File (EOF) --> not handled here
 * 		When we CTRL + D, we send a line == NULL (see in main)
*/
void	signal_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
}
