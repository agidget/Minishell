/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:57 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:58 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_ignore(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void)sig;
}

void	sig_exit(int sig)
{
	(void)sig;
	my_exit(NULL, NULL);
}

void	signals(void)
{
	signal(2, print_prompt);
	signal(11, sig_exit);
	signal(3, SIG_IGN);
}

void	sig_in_fork(void)
{
	signal(2, signal_ignore);
	signal(11, sig_exit);
	signal(3, SIG_IGN);
}
