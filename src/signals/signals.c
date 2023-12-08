/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:12:08 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/08 16:06:45 by tbarde-c         ###   ########.fr       */
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
	global_status = 128 + SIGINT;
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
	/*
	FIRST CASE : We're in the shell : 
	- CTRL + C --> print ^C and get a new prompt display
	- CTRL + \ --> do nothing
	*/
	/*if(status = IN_SHELL)
	{

	}*/
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	/*
	TO IMPLEMENT : we're executing a programm inside our shell :
	- CTRL + C --> Stop program (natural behaviour of CTRL + C)
	- CTRL + \ --> Stop program and print qui (core dump) (check what it does)
	*/
	/*if (status = IN_PROGRAM)
	{
		
	}*/
// TO implement both behaviour properly :
// - Get an int as arg for the function 
// 		- At the beginning of the prompt, initalize the signal state at 1
// 		- When we execute a prog : initialize the signal state at 2
//		- Not sure how to deal with CTRL + D, check that too
}

void	ctrl_d_handler(void)
{
	exit(0);
}