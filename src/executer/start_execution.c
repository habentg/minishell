/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:37:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/30 20:03:41 by hatesfam         ###   ########.fr       */
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
		if (id == 0)
		{
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
