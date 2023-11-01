/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:14:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/01 10:37:09 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_non_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	int	exec_return;

	if (cmd_node->iofd->fdin != -1)
		dup2(cmd_node->iofd->fdin, STDIN_FILENO);
	if (cmd_node->iofd->fdout != -1)
		dup2(cmd_node->iofd->fdout, STDOUT_FILENO);
	if (cmd_node->pipe_fd != NULL && cmd_node->pipe_fd[1] \
		&& cmd_node->pipe_fd[0])
	{
		printf("CMD: %s, pipe_fd[1]: %d\n", cmd_node->cmd, cmd_node->pipe_fd[1]);
		printf("CMD: %s, pipe_fd[0]: %d\n", cmd_node->cmd, cmd_node->pipe_fd[0]);
	}
	exec_return = execve(cmd_node->cmd, cmd_node->cmdarg, data->envi);
	if (exec_return == -1)
		return (ft_error(EXECVE_FAIL), 1);
	close_used_pipe_fds(&data->cmd_lst, &cmd_node);
	reset_std_fds(&cmd_node);
	close_cmd_fds(&cmd_node);
	return (0);
}
