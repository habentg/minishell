/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:52:48 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/08 05:39:10 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_not_found(t_cmd **cmd)
{
	g_exit_status = 127;
	printf("minishell: %s: command not found\n", (*cmd)->cmd);
}

void	file_dir_not_found(char *dir)
{
	g_exit_status = 1;
	printf("minishell: cd: %s: No such file or directory\n", dir);
}

void	ft_error(char *err_msg)
{
	ft_putendl_fd(err_msg, 1);
}
