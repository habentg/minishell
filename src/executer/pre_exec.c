/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:01:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 07:23:18 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	iofd_validity(t_iofds *iofd)
{
	if (iofd->fdin == -2)
	{
		if (access(iofd->infile, F_OK) != 0)
			return (printf("minishell: %s: No such file or \
				directory\n", iofd->infile), 1);
		if (access(iofd->infile, R_OK) != 0)
			return (printf("minishell: %s: Permission \
				denied\n", iofd->infile), 1);
	}
	if (iofd->fdout == -2)
	{
		if (access(iofd->outfile, W_OK) != 0)
			return (printf("minishell: %s: Permission \
				denied\n", iofd->outfile), 1);
	}
	return (0);
}

void	pre_exec_checks(t_data *data)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = data->cmd_lst;
	while (tmp_cmd)
	{
		check_cmd_validity(data, &tmp_cmd);
		iofd_validity(tmp_cmd->iofd);
		tmp_cmd = tmp_cmd->next;
	}
}