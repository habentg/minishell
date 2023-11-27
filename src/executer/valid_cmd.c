/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:23:12 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/28 01:34:01 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(char *cmd)
{
	struct stat	dirstat;

	ft_memset(&dirstat, 0, sizeof(dirstat));
	stat(cmd, &dirstat);
	return (S_ISDIR(dirstat.st_mode));
}

int	check_cmd_valid_utils(t_data *data, t_cmd **cmd_node)
{
	int		i;
	char	*cmd_path;
	char	*tmp_join;

	i = -1;
	cmd_path = NULL;
	tmp_join = NULL;
	while (data->path[++i])
	{
		tmp_join = ft_strjoin(data->path[i], "/");
		if (!tmp_join)
			return (display_error((*cmd_node)->cmd, strerror(errno)), 2);
		cmd_path = ft_strjoin(tmp_join, (*cmd_node)->cmd);
		free(tmp_join);
		if (access(cmd_path, F_OK) == 0)
		{
			free((*cmd_node)->cmd);
			(*cmd_node)->cmd = cmd_path;
			if (access(cmd_path, X_OK) != 0)
				return (display_error((*cmd_node)->cmd, PERMISSION_DENY), 126);
			return (0);
		}
		free(cmd_path);
	}
	return (display_error((*cmd_node)->cmd, CMD_NOT_FOUND), 127);
}

int	check_cmd_validity(t_data *data, t_cmd **cmd_node)
{
	if (!(*cmd_node)->cmd && (*cmd_node)->pipeout == 1 && \
		ft_strncmp((*cmd_node)->iofd->infile, "/tmp/.hd_temp", 13) == 0)
		return (0);
	if (!(*cmd_node)->cmd || (ft_strlen((*cmd_node)->cmd) == 0))
		return (display_error((*cmd_node)->cmd, CMD_NOT_FOUND), 127);
	if (ft_strchr((*cmd_node)->cmd, '/') != NULL)
	{
		if (access((*cmd_node)->cmd, F_OK) != 0)
			return (display_error((*cmd_node)->cmd, NO_FILE_DIR), 127);
		if (access((*cmd_node)->cmd, X_OK) != 0)
			return (display_error((*cmd_node)->cmd, PERMISSION_DENY), 126);
		if (is_directory((*cmd_node)->cmd))
			return (display_error((*cmd_node)->cmd, IS_DIRCTRY), 126);
		return (0);
	}
	if (is_builtin_cmd((*cmd_node)))
		return (0);
	data->exit_code = check_cmd_valid_utils(data, cmd_node);
	if (data->exit_code != 0)
		return (data->exit_code);
	return (0);
}
