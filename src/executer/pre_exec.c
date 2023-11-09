/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:01:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/09 19:21:53 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	iofd_validity(t_iofds *iofd)
{
	if (iofd->fdin == -2)
	{
		if (access(iofd->infile, R_OK) != 0)
			return (display_error_2(iofd->infile, PERMISSION_DENY, 1), 0);
		if (access(iofd->infile, F_OK) != 0)
			return (display_error_2(iofd->infile, NO_FILE_DIR, 1), 0);
	}
	if (iofd->fdout == -2)
		return (display_error_2(iofd->outfile, PERMISSION_DENY, 1), 0);
	return (0);
}

int	pre_exec_checks(t_data *data)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = data->cmd_lst;
	while (tmp_cmd)
	{
		if (!tmp_cmd->cmd && tmp_cmd->pipeout == 0 && ft_strncmp(tmp_cmd->iofd->\
			infile, "/tmp/.hd_temp", 13) == 0)
			return (1);
		if (check_cmd_validity(data, &tmp_cmd))
			return (1);
		if (iofd_validity(tmp_cmd->iofd))
			return (1);
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}
