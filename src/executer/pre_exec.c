/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:01:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/29 18:03:18 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	iofd_validity(t_cmd *cmd_node)
{
	if (!cmd_node->cmd)
	{
		if (cmd_node->iofd && cmd_node->iofd->outfile)
			return (-1);
		if (cmd_node->iofd && cmd_node->iofd->infile && \
			(!ft_strncmp(cmd_node->iofd->infile, "/tmp/.hd_temp_file_", 19)))
			return (-1);
	}
	if (!cmd_node->iofd)
		return (0);
	if (cmd_node->iofd->fdin == -2)
		return (1);
	if (cmd_node->iofd->fdout == -2)
		return (1);
	return (0);
}

int	pre_exec_checks(t_data *data, t_cmd *cmd_node)
{
	data->exit_code = iofd_validity(cmd_node);
	if (data->exit_code == -1)
	{
		data->exit_code = 0;
		return (1);
	}
	else if (data->exit_code)
		return (1);
	data->exit_code = check_cmd_validity(data, &cmd_node);
	if (data->exit_code)
		return (1);
	return (0);
}
