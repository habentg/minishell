/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:13:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 08:10:08 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export_add(t_data *data, t_cmd *cmd_node)
{
	(void)data;
	(void)cmd_node;
	printf("handle_export_add: [%s]\n", cmd_node->cmdarg[1]);
}

void	print_export(char **envi)
{
	int	i;

	i = 0;
	while (envi[i])
	{
		printf("declare -x %s\n", envi[i]);
		i++;
	}
}

int	handle_export(t_data *data, t_cmd *cmd_node)
{
	if (cmd_node->cmdarg[1] == NULL)
		return (print_export(data->envi), 0);
	else
	{
		if (ft_strchr(cmd_node->cmdarg[1], '=') == NULL)
		{
			g_exit_status = 1;
			return (0);
		}
		handle_export_add(data, cmd_node);
	}
	return (0);
}
