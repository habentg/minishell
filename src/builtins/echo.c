/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:51:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 06:28:59 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_echo(t_cmd *cmd_node)
{
	int	i;
	int	n_flag;
	int	fd;

	i = 1;
	n_flag = 0;
	fd = cmd_node->iofd->fdout;
	if (fd == -1)
		fd = STDOUT_FILENO;
	if (cmd_node->cmdarg[1] && \
		ft_strncmp_custom(cmd_node->cmdarg[1], "-n", 2) == 0)
		n_flag = 1;
	while (cmd_node->cmdarg[i])
	{
		if (n_flag == 1 && i == 1)
			i++;
		if (cmd_node->cmdarg[i] != NULL)
			ft_putstr_fd(cmd_node->cmdarg[i], fd);
		if (cmd_node->cmdarg[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
