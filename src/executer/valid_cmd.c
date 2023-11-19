/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:23:12 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/19 10:03:01 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			return (0);
		cmd_path = ft_strjoin(tmp_join, (*cmd_node)->cmd);
		free(tmp_join);
		if (access(cmd_path, F_OK) == 0)
		{
			free((*cmd_node)->cmd);
			(*cmd_node)->cmd = cmd_path;
			return (0);
		}
		else
			free(cmd_path);
	}
	return (1);
}

int	check_cmd_validity(t_data *data, t_cmd **cmd_node)
{
	if (!(*cmd_node)->cmd && (*cmd_node)->pipeout == 1 && \
		ft_strncmp((*cmd_node)->iofd->infile, "/tmp/.hd_temp", 13) == 0)
		return (0);
	if (!(*cmd_node)->cmd || ft_strlen((*cmd_node)->cmd) == 0)
		return (display_error((*cmd_node)->cmd, CMD_NOT_FOUND), 127);
	if (ft_strchr((*cmd_node)->cmd, '/') != NULL)
	{
		if (access((*cmd_node)->cmd, F_OK) != 0)
			return (display_error((*cmd_node)->cmd, NO_FILE_DIR), 127);
		if (access((*cmd_node)->cmd, X_OK | R_OK) != 0)
			return (display_error((*cmd_node)->cmd, PERMISSION_DENY), 126);
		return (0);
	}
	if (is_builtin_cmd((*cmd_node)))
		return (0);
	if (check_cmd_valid_utils(data, cmd_node))
		return (display_error((*cmd_node)->cmd, CMD_NOT_FOUND), 127);
	return (0);
}
