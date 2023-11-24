/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:37:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/24 20:00:13 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fork_wait(t_data *data)
{
	pid_t	ch_pid;
	int		status;
	int		ret_status;

	close_open_fds(data->cmd_lst, 0);
	ch_pid = 0;
	ret_status = 0;
	status = 0;
	while (1)
	{
		ch_pid = waitpid(-1, &status, 0);
		if (ch_pid == data->ch_pid)
		{
			if (WIFEXITED(status))
				ret_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ret_status = WTERMSIG(status) + 128;
		}
		if (ch_pid == -1 && errno == ECHILD)
			break ;
	}
	return (ret_status);
}

int	fork_and_run(t_data *data, t_cmd *tmp_cmd, pid_t *id)
{
	if (tmp_cmd->iofd->fdout != -2 && tmp_cmd->iofd->fdin != -2)
	{
		child_signals();
		*id = fork();
		if (*id == -1)
			return (ft_error(data, "Error: failed to fork!", 255), 1);
		if (*id == 0)
		{
			g_exit_status = IN_CMD;
			dup_pipe_fds(&data->cmd_lst, &tmp_cmd);
			set_iofds(data, tmp_cmd->iofd);
			close_open_fds(data->cmd_lst, 0);
			if (is_builtin_cmd(tmp_cmd))
			{
				data->exit_code = exec_builtin_cmd(tmp_cmd, data);
				return (exitshell(data, tmp_cmd, data->exit_code), \
					data->exit_code);
			}
			else
				execve(tmp_cmd->cmd, tmp_cmd->cmdarg, data->envi);
			exitshell(data, tmp_cmd, errno);
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
		}
		else if (fork_and_run(data, tmp_cmd, &data->ch_pid))
			return (ft_error(data, "Error: failed to fork!", 255), 1);
		tmp_cmd = tmp_cmd->next;
	}
	return (fork_wait(data));
}

//	case 1: if there is only one command and it is a builtin
//		# set the iofds:
//			if the command has redirections, it will point the 
//			STDIN/STDOUT to the fds of the file
//		# execute the builtin command
//			since builtin commands don't "execute" in execve, we have to 
//			manually tell the program what to do and collect the exit code,
//		# reset the iofds
//			finally, we have to reset the STDIN/STDOUT to the original fds.
//	case 2: if there are multiple commands
//		# create pipes
//			we have to create pipes for every command that has a pipeout flag
//			we have to create pipes for every command that has a pipein flag
//		# execute the commands
//			we have to execute the commands one by one
//			we have to wait for the child process to finish
//			we have to collect the exit code

int	start_execution(t_data *data)
{
	if (!data || !data->cmd_lst)
		return (0);
	if (g_exit_status == OFF_HERE_DOC)
	{
		g_exit_status = 130;
		return (0);
	}
	if (ft_dlsize(data->cmd_lst) == 1 && is_builtin_cmd(data->cmd_lst))
	{
		if (pre_exec_checks(data, data->cmd_lst))
			return (0);
		set_iofds(data, data->cmd_lst->iofd);
		data->exit_code = exec_builtin_cmd(data->cmd_lst, data);
		reset_stdio(data->cmd_lst->iofd);
	}
	else
	{
		if (create_pipes(data, data->cmd_lst))
			return (1);
		data->exit_code = exec_multiple_cmds(data);
	}
	return (0);
}
