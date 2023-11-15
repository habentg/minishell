/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:09:52 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/15 03:37:27 by hatesfam         ###   ########.fr       */
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
	perror("pwd: getcwd: error retrieving current directory");
	return (1);
}

int	handle_env(t_data *data, t_cmd *cmd_node)
{
	int	i;

	i = 0;
	(void)cmd_node;
	if (cmd_node->cmdarg[1] != NULL)
	{
		display_error_2("env", cmd_node->cmdarg[1], "too many arguments", 127);
		return (1);
	}
	while (data->envi[i])
	{
		if (ft_strchr(data->envi[i], '=') != NULL)
			printf("%s\n", data->envi[i]);
		i++;
	}
	return (0);
}

void	exec_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	if (ft_strncmp_custom(cmd_node->cmd, "cd", 2) == 0)
		g_exit_status = handle_cd(cmd_node, data);
	else if (ft_strncmp_custom(cmd_node->cmd, "pwd", 3) == 0)
		g_exit_status = handle_pwd();
	else if (ft_strncmp_custom(cmd_node->cmd, "echo", 4) == 0)
		g_exit_status = handle_echo(cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "exit", 4) == 0)
		handle_exit(data, cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "export", 6) == 0)
		g_exit_status = handle_export(data, cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "unset", 5) == 0)
		g_exit_status = handle_unset(data, cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "env", 3) == 0)
		g_exit_status = handle_env(data, cmd_node);
	return ;
}
