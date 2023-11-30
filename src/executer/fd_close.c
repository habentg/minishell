/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:00:53 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/30 18:26:04 by hatesfam         ###   ########.fr       */
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
				if (tmp->iofd->fdin > -1)
					close(tmp->iofd->fdin);
				if (tmp->iofd->fdout > -1)
					close (tmp->iofd->fdout);
			}
		}
		tmp = tmp->next;
	}
}

void	close_cmd_fds(t_cmd **cmd_node)
{
	if ((*cmd_node)->iofd->fdin > -1)
		close((*cmd_node)->iofd->fdin);
	if ((*cmd_node)->iofd->fdout > -1)
		close((*cmd_node)->iofd->fdout);
	if ((*cmd_node)->iofd->stdin_backup > -1)
		close((*cmd_node)->iofd->stdin_backup);
	if ((*cmd_node)->iofd->stdout_backup > -1)
		close((*cmd_node)->iofd->stdout_backup);
}
