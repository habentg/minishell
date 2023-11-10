/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:51:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/10 07:58:03 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_echo(t_cmd *cmd_node, int n_flag, int fd, int i_n)
{
	int	i;

	i = i_n;
	while (cmd_node->cmdarg[i])
	{
		if (cmd_node->cmdarg[i] != NULL)
			ft_putstr_fd(cmd_node->cmdarg[i], fd);
		if (cmd_node->cmdarg[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", fd);
}

int	n_option_handler(t_cmd *cmd_node)
{
	int	i_n;
	int	j_n;

	i_n = 0;
	j_n = 1;
	while (cmd_node->cmdarg[++i_n])
	{
		if (ft_strncmp(cmd_node->cmdarg[i_n], "-n", 2) == 0)
		{
			while (cmd_node->cmdarg[i_n][j_n] == 'n')
			{
				if (cmd_node->cmdarg[i_n][j_n] != 'n')
					break ;
				j_n++;
			}
			if (cmd_node->cmdarg[i_n][j_n] != '\0')
				break ;
		}
		else
			break ;
	}
	return (i_n);
}

void	handle_echo(t_cmd *cmd_node)
{
	int	n_flag;
	int	fd;
	int	i_n;
	int	j_n;

	i_n = 0;
	j_n = 1;
	n_flag = 0;
	if (cmd_node->iofd->fdout == -2 || cmd_node->iofd->fdin == -2)
		return ;
	fd = cmd_node->iofd->fdout;
	if (fd == -1)
		fd = STDOUT_FILENO;
	i_n = n_option_handler(cmd_node);
	if (i_n > 1)
		n_flag = 1;
	print_echo(cmd_node, n_flag, fd, i_n);
}
