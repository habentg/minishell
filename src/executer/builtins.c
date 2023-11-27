/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:09:52 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/28 01:53:40 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*the functio is pretty much self-descriptive*/
bool	is_builtin_cmd(t_cmd *cmd_node)
{
	if (!cmd_node->cmd || cmd_node->cmd[0] == '\0' || cmd_node->cmd[0] == ' ')
		return (false);
	if (ft_strncmp_custom(cmd_node->cmd, "echo", 4) == 0)
		return (true);
	else if (ft_strncmp_custom(cmd_node->cmd, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp_custom(cmd_node->cmd, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp_custom(cmd_node->cmd, "export", 6) == 0)
		return (true);
	else if (ft_strncmp_custom(cmd_node->cmd, "unset", 5) == 0)
		return (true);
	else if (ft_strncmp_custom(cmd_node->cmd, "env", 3) == 0)
		return (true);
	else if (ft_strncmp_custom(cmd_node->cmd, "exit", 4) == 0)
		return (true);
	return (false);
}

/*bash is basicly pulling the cwd outa his ass if 
you delete the parent directory so that what the data->cwd is for*/
int	handle_pwd(t_data *data)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		return (0);
	}
	if (data->cwd)
	{
		ft_putendl_fd(data->cwd, STDOUT_FILENO);
		return (0);
	}
	display_error_2("pwd", "getcwd", "error retrieving current directory");
	return (1);
}

/*env doesnt take options or arguments and displays 
env vars only with both key & value*/
int	handle_env(t_data *data, t_cmd *cmd_node)
{
	int	i;

	i = 0;
	(void)cmd_node;
	if (cmd_node->cmdarg[1] != NULL)
	{
		display_error_2("env", cmd_node->cmdarg[1], "too many arguments");
		return (1);
	}
	while (data->envi[i])
	{
		if (ft_strchr(data->envi[i], '=') != NULL)
			ft_putendl_fd(data->envi[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

/*this is where each of the builtins run*/
int	exec_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	data->exit_code = iofd_validity(cmd_node);
	if (data->exit_code)
		return (data->exit_code);
	if (ft_strncmp_custom(cmd_node->cmd, "cd", 2) == 0)
		data->exit_code = handle_cd(cmd_node, data);
	else if (ft_strncmp_custom(cmd_node->cmd, "pwd", 3) == 0)
		data->exit_code = handle_pwd(data);
	else if (ft_strncmp_custom(cmd_node->cmd, "echo", 4) == 0)
		data->exit_code = handle_echo(cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "exit", 4) == 0)
		handle_exit(data, cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "export", 6) == 0)
		data->exit_code = handle_export(data, cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "unset", 5) == 0)
		data->exit_code = handle_unset(data, cmd_node);
	else if (ft_strncmp_custom(cmd_node->cmd, "env", 3) == 0)
		data->exit_code = handle_env(data, cmd_node);
	return (data->exit_code);
}
