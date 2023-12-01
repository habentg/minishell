/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:00:53 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/01 19:21:12 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
