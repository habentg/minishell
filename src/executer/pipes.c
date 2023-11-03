/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:15:11 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 14:49:01 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipes(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		*tmp_pipe;

	tmp_cmd = cmd;
	// tmp_pipe = NULL;
	while (tmp_cmd)
	{
		if (tmp_cmd->pipeout == 1 || (tmp_cmd->prev && \
			tmp_cmd->prev->pipeout == 1))
		{
			tmp_pipe = (int *)malloc(sizeof(int) * 2);
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

void	dup_pipe_fds(t_cmd **cmd_lst, t_cmd **cmd_node)
{
	// backup_std_fds(cmd_node);
	// (void)cmd_lst;
	if ((*cmd_node)->pipeout == 1)
		dup2((*cmd_node)->pipe_fd[1], STDOUT_FILENO);
	if ((*cmd_node)->prev && (*cmd_node)->prev->pipeout == 1)
		dup2((*cmd_node)->prev->pipe_fd[0], STDIN_FILENO);
	close_unused_pipe_fds(cmd_lst, cmd_node);
}
