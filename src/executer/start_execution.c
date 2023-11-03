/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:37:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 06:48:40 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	start_execution(t_data *data)
{
	t_cmd	*tmp_cmd;
	pid_t	id;

	tmp_cmd = data->cmd_lst;
	(void)id;
	if (create_pipes(data->cmd_lst))
		return (1);
	while (tmp_cmd)
	{
		if (is_builtin_cmd(tmp_cmd))
			exec_builtin_cmd(tmp_cmd, data);
	// 	else
	// 	{
	// 		printf("tmp_cmd->cmd: %s\n", tmp_cmd->cmd);
	// 		id = fork();
	// 		if (id == -1)
	// 			return (ft_error("Error: failed to fork!"), 1);
	// 		dup_pipe_fds(&data->cmd_lst, &tmp_cmd);
	// 		if (id == 0)
	// 			execute_non_builtin_cmd(tmp_cmd, data);
	// 		else
	// 		{
	// 			waitpid(id, 0, 0);
	// 			reset_std_fds(&tmp_cmd);
	// 		}
	// 	}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}
