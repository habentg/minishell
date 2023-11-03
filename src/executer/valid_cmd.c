/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:23:12 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 06:55:49 by hatesfam         ###   ########.fr       */
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
	if (ft_strchr((*cmd_node)->cmd, '/') != NULL)
	{
		if (access((*cmd_node)->cmd, F_OK | X_OK) == 0)
			return (0);
		else
			return (cmd_not_found(cmd_node), 1);
	}
	if (is_builtin_cmd((*cmd_node)))
		return (0);
	if (check_cmd_valid_utils(data, cmd_node))
		return (cmd_not_found(cmd_node), 1);
	return (0);
}
