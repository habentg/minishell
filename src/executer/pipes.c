/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:15:11 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/30 19:57:05 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipes(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		*tmp_pipe;

	tmp_cmd = cmd;
	tmp_pipe = NULL;
	while (tmp_cmd)
	{
		if (tmp_cmd->pipeout == 1 || (tmp_cmd->prev && tmp_cmd->prev->pipeout))
		{
			tmp_pipe = malloc(sizeof(int) * 2);
			if (!tmp_pipe)
				return (ft_error(PIPE_MALLOC_ERROR), 1);
			if (pipe(tmp_pipe) == -1)
				return (ft_error(PIPE_FUNC_ERROR), 1);
			tmp_cmd->pipe_fd = tmp_pipe;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}

void	backup_std_fds(t_cmd **cmd_node)
{
	(*cmd_node)->iofd->stdin_backup = dup(STDIN_FILENO);
	(*cmd_node)->iofd->stdout_backup = dup(STDOUT_FILENO);
	close((*cmd_node)->iofd->stdin_backup);
	close((*cmd_node)->iofd->stdout_backup);
}

void	reset_std_fds(t_cmd **cmd_node)
{
	dup2(STDIN_FILENO, (*cmd_node)->iofd->stdin_backup);
	dup2(STDOUT_FILENO, (*cmd_node)->iofd->stdout_backup);
	close((*cmd_node)->iofd->stdin_backup);
	close((*cmd_node)->iofd->stdout_backup);
}

void	dup_pipe_fds(t_cmd **cmd_node)
{
	if ((*cmd_node)->pipeout == 1)
		dup2((*cmd_node)->iofd->fdout, STDOUT_FILENO);
	if ((*cmd_node)->prev && (*cmd_node)->prev->pipeout == 1)
		dup2((*cmd_node)->iofd->fdin, STDIN_FILENO);
	close((*cmd_node)->iofd->fdout);
	close((*cmd_node)->iofd->fdin);
}

void	close_fds(t_cmd **cmd_node)
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
