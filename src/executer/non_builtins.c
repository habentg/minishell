/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:14:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 15:13:08 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_non_builtin_cmd(t_cmd *cmd_node, t_data *data)
{
	if (execve(cmd_node->cmd, cmd_node->cmdarg, data->envi))
		return (ft_error(EXECVE_FAIL), 1);
	return (0);
}
