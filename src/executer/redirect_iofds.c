/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_iofds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:26:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/25 12:56:39 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_iofds(t_data *data, t_iofds *iofds)
{
	if (!iofds || (iofds->fdin == -1 && iofds->fdout == -1))
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
