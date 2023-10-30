/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:09:52 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/30 16:05:59 by hatesfam         ###   ########.fr       */
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

void	exec_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	(void)data;
	(void)cmd_node;
	printf("Builtins will be handled later ------ slow down!\n");
}
