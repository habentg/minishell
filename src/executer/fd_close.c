/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:00:53 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/03 05:12:11 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_unused_pipe_fds(t_cmd **cmd_lst, t_cmd *cmd_node)
{
	t_cmd	*tmp;

	tmp = *cmd_lst;
	while (tmp)
	{
		if (tmp != cmd_node && tmp->pipe_fd)
		{
			close(tmp->pipe_fd[0]);
			close(tmp->pipe_fd[1]);
			if (tmp->iofd)
			{
				if (tmp->iofd->fdin != -1)
					close(tmp->iofd->fdin);
				if (tmp->iofd->fdout != -1)
					close (tmp->iofd->fdout);
			}
		}
		tmp = tmp->next;
	}
}

void	close_all_file_descriptors(t_cmd *cmd_lst)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = cmd_lst;
	while (tmp_cmd)
	{
		if (tmp_cmd->pipe_fd)
		{
			close(tmp_cmd->pipe_fd[0]);
			close(tmp_cmd->pipe_fd[1]);
		}
		if (tmp_cmd->iofd)
		{
			if (tmp_cmd->iofd->fdin != -1)
				close(tmp_cmd->iofd->fdin);
			if (tmp_cmd->iofd->fdout != -1)
				close(tmp_cmd->iofd->fdout);
			if (tmp_cmd->iofd->stdin_backup != -1)
				close(tmp_cmd->iofd->stdin_backup);
			if (tmp_cmd->iofd->stdout_backup != -1)
				close(tmp_cmd->iofd->stdout_backup);
		}
		tmp_cmd = tmp_cmd->next;
	}
}
