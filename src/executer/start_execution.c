/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:37:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/01 07:48:30 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	start_execution(t_data *data)
{
	t_cmd	*tmp_cmd;
	int		id;

	tmp_cmd = data->cmd_lst;
	if (create_pipes(data->cmd_lst))
		return (1);
	while (tmp_cmd)
	{
		id = fork();
		if (id == -1)
			return (ft_error("Error: forking failure!"), 1);
		if (id == 0)
		{
			dup_pipe_fds(&data->cmd_lst, &tmp_cmd);
			if (is_builtin_cmd(tmp_cmd))
				exec_builtin_cmd(tmp_cmd, data);
			else
				if (execute_non_builtin_cmd(tmp_cmd, data))
					return (1);
		}
		else
			waitpid(id, 0, 0);
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}
