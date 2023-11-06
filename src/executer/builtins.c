/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:09:52 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 17:03:25 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_cmd(t_cmd *cmd_node)
{
	if (ft_strncmp_custom(cmd_node->cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp_custom(cmd_node->cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp_custom(cmd_node->cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp_custom(cmd_node->cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp_custom(cmd_node->cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp_custom(cmd_node->cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp_custom(cmd_node->cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

int	handle_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		printf("%s\n", path);
		return (0);
	}
	perror("getcwd error in handle_pwd");
	return (1);
}

void	handle_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envi[i])
	{
		if (ft_strchr(data->envi[i], '=') != NULL)
			printf("%s\n", data->envi[i]);
		i++;
	}
}

void	exec_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	if (ft_strncmp_custom(cmd_node->cmd, "cd", 2) == 0)
		handle_cd(cmd_node, data);
	else if (ft_strncmp_custom(cmd_node->cmd, "pwd", 3) == 0)
	{
		if (handle_pwd())
			return ;
	}
	else if (ft_strncmp_custom(cmd_node->cmd, "echo", 4) == 0)
		handle_echo(cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "exit", 4) == 0)
	{
		if (handle_exit(data, cmd_node))
			return ;
	}
	else if (ft_strncmp_custom(cmd_node->cmd, "export", 6) == 0)
		handle_export(data, cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "unset", 5) == 0)
		handle_unset(data, cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "env", 3) == 0)
		handle_env(data);
}
