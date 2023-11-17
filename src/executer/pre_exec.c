/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:01:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/17 15:47:53 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	iofd_validity(t_data *data, t_iofds *iofd)
{
	(void)data;
	if (iofd->fdin == -2)
	{
		if (access(iofd->infile, F_OK) != 0)
			return (display_error(iofd->infile, NO_FILE_DIR, 127), 1);
		if (access(iofd->infile, R_OK | X_OK) != 0)
			return (display_error(iofd->infile, PERMISSION_DENY, 126), 1);
	}
	if (iofd->fdout == -2)
		return (display_error(iofd->outfile, PERMISSION_DENY, 1), 1);
	return (0);
}

int	pre_exec_checks(t_data *data, t_cmd *cmd_node)
{
	if (!cmd_node->cmd && cmd_node->pipeout == 0 && ft_strncmp(cmd_node->iofd->\
		infile, "/tmp/.hd_temp", 13) == 0)
		return (1);
	data->exit_code = iofd_validity(data, cmd_node->iofd);
	if (data->exit_code)
		return (1);
	data->exit_code = check_cmd_validity(data, &cmd_node);
	if (data->exit_code)
		return (1);
	return (0);
}
