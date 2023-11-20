/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:37:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/20 13:19:39 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	fork_wait(t_data *data)
// {
// 	pid_t	ch_pid;
// 	int		status;
// 	int		ret_status;

// 	close_open_fds(data->cmd_lst, 0);
// 	ch_pid = 0;
// 	ret_status = 0;
// 	status = 0;
// 	while (1)
// 	{
// 		ch_pid = waitpid(-1, &status, 0);
// 		if (ch_pid == data->ch_pid)
// 			ret_status = status;
// 		if (ch_pid == -1 && errno == ECHILD)
// 			break ;
// 	}
// 	if (WIFEXITED(status))
// 		ret_status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		ret_status = WTERMSIG(status) + 128;
// 	return (ret_status);
// }

int	fork_wait(t_data *data)
{
	pid_t	pid;
	int		status;
	int		res;

	close_open_fds(data->cmd_lst, 0);
	res = 0;
	pid = 0;
	while (pid != -1 || errno != ECHILD)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == data->ch_pid)
			res = status;
		continue ;
	}
	if (WIFSIGNALED(res))
		status = 128 + WTERMSIG(res);
	else if (WIFEXITED(res))
		status = WEXITSTATUS(res);
	else
		status = res;
	return (status);
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

int	exec_multiple_cmds(t_data *data)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = data->cmd_lst;
	while (tmp_cmd && data->ch_pid != 0)
	{
		if (pre_exec_checks(data, tmp_cmd))
		{
			if (!tmp_cmd->next)
				return (data->exit_code);
			tmp_cmd = tmp_cmd->next;
			continue ;
		}
		if (fork_and_run(data, tmp_cmd, &data->ch_pid))
			return (ft_error(data, "Error: failed to fork!", 255), 1);
		tmp_cmd = tmp_cmd->next;
	}
	return (fork_wait(data));
}

int	start_execution(t_data *data)
{
	if (!data || !data->cmd_lst)
		return (0);
	if (ft_dlsize(data->cmd_lst) == 1 && is_builtin_cmd(data->cmd_lst))
		exec_builtin_cmd(data->cmd_lst, data);
	else
	{
		if (create_pipes(data, data->cmd_lst))
			return (1);
		data->exit_code = exec_multiple_cmds(data);
	}
	return (0);
}
