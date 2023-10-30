/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:14:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/30 19:38:18 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_non_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	int	exec_return;

	backup_std_fds(&cmd_node);
	if (cmd_node->iofd->fdin != -1)
		dup2(cmd_node->iofd->fdin, STDIN_FILENO);
	if (cmd_node->iofd->fdout != -1)
		dup2(cmd_node->iofd->fdout, STDOUT_FILENO);
	close_fds(&cmd_node);
	if (cmd_node->pipeout == 1 || (cmd_node->prev && \
		cmd_node->prev->pipeout == 1))
		dup_pipe_fds(&cmd_node);
	exec_return = execve(cmd_node->cmd, cmd_node->cmdarg, data->envi);
	if (exec_return == -1)
		return (ft_error(EXECVE_FAIL), 1);
	reset_std_fds(&cmd_node);
	return (0);
}
