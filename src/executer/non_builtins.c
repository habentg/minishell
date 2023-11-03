/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:14:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/02 22:04:30 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_non_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	printf("cmd_node->cmd: %s\n", cmd_node->cmd);
	// if (cmd_node->iofd->fdin != -1)
	// 	dup2(cmd_node->iofd->fdin, STDIN_FILENO);
	// if (cmd_node->iofd->fdout != -1)
	// 	dup2(cmd_node->iofd->fdout, STDOUT_FILENO);
	if (execve(cmd_node->cmd, cmd_node->cmdarg, data->envi))
		return (ft_error(EXECVE_FAIL), 1);
	return (0);
}
