/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:51:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 06:03:20 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_echo(t_cmd *cmd_node, int n_flag, int fd)
{
	int	i;

	i = 1;
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
}

int	handle_echo(t_cmd *cmd_node)
{
	int	i;
	int	n_flag;
	int	fd;

	i = 1;
	n_flag = 0;
	if (cmd_node->iofd->fdout == -2 || cmd_node->iofd->fdin == -2)
		return (1);
	fd = cmd_node->iofd->fdout;
	if (fd == -1)
		fd = STDOUT_FILENO;
	if (cmd_node->cmdarg[1] && \
		ft_strncmp_custom(cmd_node->cmdarg[1], "-n", 2) == 0)
		n_flag = 1;
	print_echo(cmd_node, n_flag, fd);
	return (0);
}
