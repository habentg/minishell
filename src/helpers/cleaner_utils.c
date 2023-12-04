/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 05:08:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/26 16:05:58 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_delone_token(t_token *lst)
{
	if (lst && lst->str)
	{
		free(lst->str);
		lst->str = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
}

void	ft_free_iofile(t_iofds *iofiles)
{
	if (!iofiles)
		return ;
	if (iofiles->infile)
	{
		if (iofiles->fdin >= -1)
			close(iofiles->fdin);
		free(iofiles->infile);
	}
	if (iofiles->outfile)
	{
		if (iofiles->fdout >= -1)
			close(iofiles->fdout);
		free(iofiles->outfile);
	}
	if (iofiles->here_delemiter)
		free(iofiles->here_delemiter);
	free(iofiles);
}

void	free_cmdnode(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmdarg)
		ft_clean_arr(cmd->cmdarg);
	if (cmd->iofd)
		ft_free_iofile(cmd->iofd);
	if (cmd->pipe_fd)
		free(cmd->pipe_fd);
}
