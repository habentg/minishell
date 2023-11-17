/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:05:20 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/10 19:05:35 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    sig_doc(int sig)
{
    (void)sig;
    g_exit_status = 1;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
}


/* void    sig_doc(int sig)
{
    if (sig == SIGINT)
    {
        g_exit_status = 127;
        return ((void)g_exit_status);
    }
} */

void    sig_c_for_functions(int sig)
{
    (void)sig;
    // g_exit_status = 127;
    //printf("\033[1;34m[%d]\033[0m", g_exit_status);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    sig_c(int sig)
{
    (void)sig;
    g_exit_status = 127;
    printf("\n");
    tputs(tgetstr("dl", NULL), 1, putchar);
    printf("\033[1;34m[%d]\033[0m", g_exit_status);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    sig_handler(void)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sig_c);
}
