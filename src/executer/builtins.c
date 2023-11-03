/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:09:52 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 03:13:26 by hatesfam         ###   ########.fr       */
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
	else
	{
		perror("getcwd");
		return (1);
	}
}


/*if only cd is given, find 'HOME' in the path and chdir to there*/
/*else, change to the path given give after 'cd', idk what comes after that*/
int	handle_cd(t_cmd *cmd_node, t_data *data)
{
	char	*path;

	if (cmd_node->cmdarg[1] == NULL || \
		ft_strncmp_custom(cmd_node->cmdarg[1], "~", 1) == 0)
	{
		path = get_path(data->envi, "HOME");
		if (path == NULL)
			return (ft_error("Error: HOME not set"), 1);
	}
	else
		path = cmd_node->cmdarg[1];
	if (chdir(path) == -1)
		return (ft_error("Error: chdir failure"), 1);
	return (0);
}

void	handle_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envi[i])
	{
		printf("%s\n", data->envi[i]);
		i++;
	}
}

void	exec_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	if (ft_strncmp_custom(cmd_node->cmd, "cd", 2) == 0)
	{
		if (handle_cd(cmd_node, data))
			return ;
	}
	else if (ft_strncmp_custom(cmd_node->cmd, "pwd", 3) == 0)
	{
		if (handle_pwd())
			return ;
	}
	else if (ft_strncmp_custom(cmd_node->cmd, "echo", 4) == 0)
	{
		if (handle_echo(cmd_node))
			return ;
	}
	else if (ft_strncmp_custom(cmd_node->cmd, "exit", 4) == 0)
	{
		if (handle_exit(data, cmd_node))
			return ;
	}
	else if (ft_strncmp_custom(cmd_node->cmd, "export", 6) == 0)
	{
		if (handle_export(data, cmd_node))
			return ;
	}
	else if (ft_strncmp_custom(cmd_node->cmd, "env", 3) == 0)
		handle_env(data);
	else
		printf("chilll we not there yet!\n");
}
