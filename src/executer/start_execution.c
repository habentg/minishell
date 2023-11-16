/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:37:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/16 18:36:59 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fork_wait(t_data *data)
{
	pid_t	ch_pid;
	int		status;

	close_open_fds(data->cmd_lst, 0);
	ch_pid = 0;
	while (1)
	{
		ch_pid = waitpid(-1, &status, 0);
		if (ch_pid == -1 && errno == ECHILD)
			break ;
	}
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		data->exit_code = WTERMSIG(status) + 128;
	printf("pid: %d\n", ch_pid);
	printf("status: %d\n", status);
	printf("exit code: %d\n", data->exit_code);
	return (data->exit_code);
}

int	fork_and_run(t_data *data, t_cmd *tmp_cmd, pid_t *id)
{
	if (tmp_cmd->iofd->fdout != -2 && tmp_cmd->iofd->fdin != -2)
	{
		child_signals(tmp_cmd);
		*id = fork();
		if (*id == -1)
			return (ft_error(data, "Error: failed to fork!", 255), 1);
		if (*id == 0)
		{
			dup_pipe_fds(&data->cmd_lst, &tmp_cmd);
			set_redirections(data, tmp_cmd->iofd);
			close_open_fds(data->cmd_lst, 0);
			if (is_builtin_cmd(tmp_cmd))
				exec_builtin_cmd(tmp_cmd, data);
			else
				execve(tmp_cmd->cmd, tmp_cmd->cmdarg, data->envi);
			exitshell(data, tmp_cmd, 1);
		}
	}
	return (0);
}

void	exec_multiple_cmds(t_data *data)
{
	t_cmd	*tmp_cmd;
	pid_t	id;

	tmp_cmd = data->cmd_lst;
	id = 1;
	while (tmp_cmd && id != 0)
	{
		if (fork_and_run(data, tmp_cmd, &id))
			return ;
		tmp_cmd = tmp_cmd->next;
	}
	fork_wait(data);
}

int	start_execution(t_data *data)
{
	if (pre_exec_checks(data))
		return (0);
	if (ft_dlsize(data->cmd_lst) == 1 && is_builtin_cmd(data->cmd_lst))
		exec_builtin_cmd(data->cmd_lst, data);
	else
	{
		if (create_pipes(data, data->cmd_lst))
			return (1);
		exec_multiple_cmds(data);
	}
	return (0);
}
