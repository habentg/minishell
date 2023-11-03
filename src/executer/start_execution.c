/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:37:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 16:20:38 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_redirections(t_iofds *iofd)
{
	if (!iofd)
		return ;
	iofd->stdin_backup = dup(STDIN_FILENO);
	if (iofd->stdin_backup == -1)
		return ;
	iofd->stdout_backup = dup(STDOUT_FILENO);
	if (iofd->stdout_backup == -1)
		return ;
	if (iofd->fdin != -1) 
	{
		if (dup2(iofd->fdin, STDIN_FILENO) == -1)
		{
			ft_error(strerror(errno));
			return ;
		}
	}
	if (iofd->fdout != -1)
	{
		if (dup2(iofd->fdout, STDOUT_FILENO) == -1)
		{
			ft_error(strerror(errno));
			return ;
		}
	}

}

void	reset_stdio(t_iofds *iofds)
{
	if (!iofds)
		return ;
	if (iofds->stdin_backup != -1)
	{
		if (dup2(iofds->stdin_backup, STDIN_FILENO) == -1)
			return ;
		close(iofds->stdin_backup);
		iofds->stdin_backup = -1;
	}
	if (iofds->stdout_backup != -1)
	{
		if (dup2(iofds->stdout_backup, STDOUT_FILENO) == -1)
			return ;
		close(iofds->stdout_backup);
		iofds->stdout_backup = -1;
	}
	return ;
}

void	close_unused_pipes_2(t_cmd *headcmd, t_cmd *curcmd)
{
	while (headcmd)
	{
		if (headcmd != curcmd && headcmd->pipe_fd)
		{
			close(headcmd->pipe_fd[0]);
			close(headcmd->pipe_fd[1]);
			if (headcmd->iofd)
			{
				if (headcmd->iofd->fdin != -1)
					close(headcmd->iofd->fdin);
				if (headcmd->iofd->fdout != -1)
					close (headcmd->iofd->fdout);
			}
		}
		headcmd = headcmd->next;
	}
	return ;
}

void	close_open_fds(t_cmd *cmd_lst, int exc_ended)
{
	if (cmd_lst->iofd)
	{
		if (cmd_lst->iofd->fdin != -1)
			close(cmd_lst->iofd->fdin);
		if (cmd_lst->iofd->fdout != -1)
			close (cmd_lst->iofd->fdout);
		if (exc_ended == 1)
		{
			reset_stdio(cmd_lst->iofd);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
		}
	}
	// close_unused_pipe_fds(&cmd_lst, NULL);
	close_unused_pipes_2(cmd_lst, NULL);
}

void	exitshell(t_data *data, int excode)
{
	if (data)
	{
		if (data->cmd_lst && data->cmd_lst->iofd)
			close_open_fds(data->cmd_lst, 1);
		ft_clean_data(&data);
	}
	exit(excode);
}

int	fork_wait(t_data *data)
{
	pid_t	ch_pid;
	int		status;
	int		res;

	close_open_fds(data->cmd_lst, 0);
	res = 0;
	ch_pid = 0;
	while (ch_pid != -1 || errno != ECHILD)
	{
		ch_pid = waitpid(-1, &status, 0);
		if (ch_pid == 0)
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



int	start_execution(t_data *data)
{
	t_cmd	*tmp_cmd;
	pid_t	id;

	tmp_cmd = data->cmd_lst;
	if (create_pipes(data->cmd_lst))
		return (1);
	id = 1;
	while (tmp_cmd && id != 0)
	{
		// if (is_builtin_cmd(tmp_cmd))
		// 	exec_builtin_cmd(tmp_cmd, data);
		// else
		// {
		// 	printf("tmp_cmd->cmd: %s\n", tmp_cmd->cmd);
			id = fork();
			if (id == -1)
				return (ft_error("Error: failed to fork!"), 1);
			if (id == 0)
			{
				dup_pipe_fds(&data->cmd_lst, &tmp_cmd);
				set_redirections(tmp_cmd->iofd);
				close_open_fds(data->cmd_lst, 0);
				if (is_builtin_cmd(tmp_cmd))
					exec_builtin_cmd(tmp_cmd, data);
				else
					execute_non_builtin_cmd(tmp_cmd, data);
				exitshell(data, 1);
			}

		// }
		tmp_cmd = tmp_cmd->next;
	}
	fork_wait(data);
	
	// waitpid(id, 0, 0);
	// reset_std_fds(&tmp_cmd);

			
	return (0);
}
