/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:05:20 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/25 23:16:49 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_signal_handler(int num)
{
	if (num == SIGINT)
		write(1, "\n", 1);
	else if (num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

void	child_signals(void)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
}

int	event(void)
{
	return (0);
}

void	sigint_handler(int sig)
{
	(void) sig;
	if (g_exit_status == IN_MINI || g_exit_status == IN_CMD)
	{
		g_exit_status = 130;
		write(1, "^C", 2);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
	}
	else if (g_exit_status == IN_HERE_DOC)
	{
		g_exit_status = OFF_HERE_DOC;
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

int	init_signals(void)
{
	rl_catch_signals = 0;
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (g_exit_status);
}
