/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:00:53 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/01 09:47:38 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_std_fds(t_cmd **cmd_node)
{
	dup2(STDIN_FILENO, (*cmd_node)->iofd->stdin_backup);
	dup2(STDOUT_FILENO, (*cmd_node)->iofd->stdout_backup);
	close((*cmd_node)->iofd->stdin_backup);
	close((*cmd_node)->iofd->stdout_backup);
	(*cmd_node)->iofd->stdin_backup = -1;
	(*cmd_node)->iofd->stdout_backup = -1;
}

void	backup_std_fds(t_cmd **cmd_node)
{
	(*cmd_node)->iofd->stdin_backup = dup(STDIN_FILENO);
	(*cmd_node)->iofd->stdout_backup = dup(STDOUT_FILENO);
}

void	close_used_pipe_fds(t_cmd **cmd_lst, t_cmd **cmd_node)
{
	(void)cmd_lst;
	if ((*cmd_node)->pipe_fd != NULL && (*cmd_node)->pipe_fd[1])
		close((*cmd_node)->pipe_fd[1]);
	if ((*cmd_node)->pipe_fd != NULL && (*cmd_node)->pipe_fd[0])
		close((*cmd_node)->pipe_fd[0]);
}

void	close_unused_pipe_fds(t_cmd **cmd_lst, t_cmd **cmd_node)
{
	t_cmd	*curr_cmd;

	curr_cmd = *cmd_lst;
	while (curr_cmd)
	{
		if (curr_cmd != (*cmd_node) && curr_cmd->pipe_fd)
		{
			if (curr_cmd->pipe_fd[0])
				close(curr_cmd->pipe_fd[0]);
			if (curr_cmd->pipe_fd[1])
				close(curr_cmd->pipe_fd[1]);
			close_cmd_fds(&curr_cmd);
		}
		curr_cmd = curr_cmd->next;
	}
}

void	close_cmd_fds(t_cmd **cmd_node)
{
	if ((*cmd_node)->iofd->fdin != -1)
		close((*cmd_node)->iofd->fdin);
	if ((*cmd_node)->iofd->fdout != -1)
		close((*cmd_node)->iofd->fdout);
	if ((*cmd_node)->iofd->stdin_backup != -1)
		close((*cmd_node)->iofd->stdin_backup);
	if ((*cmd_node)->iofd->stdout_backup != -1)
		close((*cmd_node)->iofd->stdout_backup);
}
