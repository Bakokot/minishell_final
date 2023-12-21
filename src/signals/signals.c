/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:12:08 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/21 09:29:31 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_prompt(void)
{
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * Normal ctrl + c behaviour in shell
*/
static void	ctrl_c_handler(int sig)
{
	(void)sig;
	g_exit_status = 128 + SIGINT;
	new_prompt();
}

/**
 * ctrl + c behaviour when we're in a program executed in the minishell
*/
static void	ctrl_c_prog(int sig)
{
	(void)sig;
	g_exit_status = 128 + SIGINT;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
}

/**
 * ctrl + \ behaviour when we're in a program executed in the minishell
*/
static void	backslash_handler(int sig)
{
	(void)sig;
	g_exit_status = 128 + SIGQUIT;
	write(1, "Quit (core dumped)", 19);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
}

/**
 * When we're IN_SHELL :
 * [Ctrl + \]	SIGQUIT --> ignored
 * [CTRL + C]	SIGINT --> print ^C and make a new prompt
 * [CTRL + D]	End Of File (EOF) --> not handled here
 * 		When we CTRL + D, we send a line == N#ULL (see in main)
 * ELSE we want to reset the typical behaviour 
 * of the signals when we're IN_PROGRAM
*/
void	signal_handling(int status)
{
	if (status == IN_SHELL)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c_handler);
	}
	if (status == IN_PROGRAM)
	{
		signal(SIGQUIT, backslash_handler);
		signal(SIGINT, ctrl_c_prog);
	}
}
