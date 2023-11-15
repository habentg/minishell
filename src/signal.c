/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:05:20 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/15 13:53:34 by hatesfam         ###   ########.fr       */
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

void	sig_p_process(int sig)
{
	if (sig == SIGINT)
	{
		if (waitpid(-1, &g_exit_status, WNOHANG) == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_exit_status = 1;
		}
	}
}

void	child_signals(t_cmd *cmd)
{
	(void)cmd;
	// if (ft_strcmp(cmd->input.name, "here_doc") != 0)
	// {
		signal(SIGINT, child_signal_handler);
		signal(SIGQUIT, child_signal_handler);
	// }
}

void	sig_handler(void)
{
	signal(SIGINT, sig_p_process);
	signal(SIGQUIT, SIG_IGN);
}
