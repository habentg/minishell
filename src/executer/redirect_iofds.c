/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_iofds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:26:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/21 11:46:12 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_redirections(t_data *data, t_iofds *iofd)
{
	if (!iofd)
		return (1);
	iofd->stdin_backup = dup(STDIN_FILENO);
	if (iofd->stdin_backup == -1)
		return (1);
	iofd->stdout_backup = dup(STDOUT_FILENO);
	if (iofd->stdout_backup == -1)
		return (1);
	if (iofd->fdin != -1)
	{
		if (dup2(iofd->fdin, STDIN_FILENO) == -1)
			return (ft_error(data, FD_DUP_FAILED, errno), 1);
	}
	if (iofd->fdout != -1)
	{
		if (dup2(iofd->fdout, STDOUT_FILENO) == -1)
			return (ft_error(data, FD_DUP_FAILED, errno), 1);
	}
	return (0);
}

void	set_iofds(t_data *data, t_iofds *iofds)
{
	if (!iofds)
		return ;
	iofds->stdin_backup = dup(STDIN_FILENO);
	if (iofds->stdin_backup == -1)
		return ;
	iofds->stdout_backup = dup(STDOUT_FILENO);
	if (iofds->stdout_backup == -1)
		return ;
	if (iofds->fdin != -1)
	{
		if (dup2(iofds->fdin, STDIN_FILENO) == -1)
			ft_error(data, FD_DUP_FAILED, errno);
	}
	if (iofds->fdout != -1)
	{
		if (dup2(iofds->fdout, STDOUT_FILENO) == -1)
			ft_error(data, FD_DUP_FAILED, errno);
	}
	return ;
}

void	reset_stdio(t_iofds *iofds)
{
	if (!iofds)
		return ;
	if (iofds->stdin_backup != -1)
	{
		if (dup2(iofds->stdin_backup, STDIN_FILENO) == -1)
			return ;
		close(iofds->stdin_backup);
		iofds->stdin_backup = -1;
	}
	if (iofds->stdout_backup != -1)
	{
		if (dup2(iofds->stdout_backup, STDOUT_FILENO) == -1)
			return ;
		close(iofds->stdout_backup);
		iofds->stdout_backup = -1;
	}
	return ;
}
