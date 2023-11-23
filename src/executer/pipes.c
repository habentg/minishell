/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:15:11 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/23 14:19:56 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipes(t_data *data, t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		*tmp_pipe;

	tmp_cmd = cmd;
	while (tmp_cmd)
	{
		if (tmp_cmd->pipeout == 1 || (tmp_cmd->prev && \
			tmp_cmd->prev->pipeout == 1))
		{
			tmp_pipe = (int *)malloc(sizeof(int) * 2);
			if (!tmp_pipe)
				return (ft_error(data, PIPE_MALLOC_ERROR, 255), 1);
			if (pipe(tmp_pipe) == -1)
				return (ft_error(data, PIPE_FUNC_ERROR, 255), 1);
			tmp_cmd->pipe_fd = tmp_pipe;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}

void	dup_pipe_fds(t_cmd **cmd_lst, t_cmd **cmd_node)
{
	if (!*cmd_node)
		return ;
	if ((*cmd_node)->pipeout == 1)
		dup2((*cmd_node)->pipe_fd[1], STDOUT_FILENO);
	if ((*cmd_node)->prev && (*cmd_node)->prev->pipeout == 1)
		dup2((*cmd_node)->prev->pipe_fd[0], STDIN_FILENO);
	close_unused_pipe_fds(cmd_lst, *cmd_node);
}

void	close_open_fds(t_cmd *cmd_lst, int exc_ended)
{
	if (cmd_lst->iofd)
	{
		if (cmd_lst->iofd->fdin != -1)
			close(cmd_lst->iofd->fdin);
		if (cmd_lst->iofd->fdout != -1)
			close (cmd_lst->iofd->fdout);
		if (exc_ended == 1)
		{
			reset_stdio(cmd_lst->iofd);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
		}
	}
	close_unused_pipe_fds(&cmd_lst, NULL);
}

void	exitshell(t_data *data, t_cmd *cmdnode, int excode)
{
	data->exit_code = excode;
	if (cmdnode && cmdnode->iofd)
		close_open_fds(data->cmd_lst, 1);
	ft_clean_data_done(&data, 1);
}
