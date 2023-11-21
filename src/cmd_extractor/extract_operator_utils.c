/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operator_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:41:16 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/21 13:02:29 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_prev_iofdins(t_cmd **cmd_node, t_token **token)
{
	if ((*cmd_node)->iofd->fdout == -2 || (*cmd_node)->iofd->fdin == -2)
	{
		(*token) = (*token)->next->next;
		return (1);
	}
	if ((*cmd_node)->iofd->fdin > -1)
	{
		close((*cmd_node)->iofd->fdin);
		(*cmd_node)->iofd->fdin = -1;
	}
	if ((*cmd_node)->iofd->here_delemiter != NULL)
	{
		free((*cmd_node)->iofd->here_delemiter);
		(*cmd_node)->iofd->here_delemiter = NULL;
		unlink((*cmd_node)->iofd->infile);
	}
	if ((*cmd_node)->iofd->infile)
	{
		free((*cmd_node)->iofd->infile);
		(*cmd_node)->iofd->infile = NULL;
		unlink((*cmd_node)->iofd->infile);
	}
	return (0);
}

int	remove_prev_iofdouts(t_cmd **cmd_node, t_token **token)
{
	if ((*cmd_node)->iofd->fdout == -2 || (*cmd_node)->iofd->fdin == -2)
	{
		(*token) = (*token)->next->next;
		return (1);
	}
	if ((*cmd_node)->iofd->fdout > -1)
	{
		close((*cmd_node)->iofd->fdout);
		(*cmd_node)->iofd->fdout = -1;
	}
	if ((*cmd_node)->iofd->outfile)
	{
		free((*cmd_node)->iofd->outfile);
		(*cmd_node)->iofd->outfile = NULL;
		unlink((*cmd_node)->iofd->outfile);
	}
	return (0);
}
