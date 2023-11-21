/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:51:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/21 11:37:09 by hatesfam         ###   ########.fr       */
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

bool	is_n_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	n_option_handler(t_cmd *cmd_node)
{
	int	i_n;

	i_n = 0;
	while (cmd_node->cmdarg[++i_n])
	{
		if (ft_strncmp(cmd_node->cmdarg[i_n], "-n", 2) == 0)
		{
			if (is_n_only(&cmd_node->cmdarg[i_n][1]) == false)
				break ;
		}
		else
			break ;
	}
	return (i_n);
}

int	handle_echo(t_cmd *cmd_node)
{
	int	n_flag;
	int	i_n;

	i_n = 0;
	n_flag = 0;
	i_n = n_option_handler(cmd_node);
	if (i_n > 1)
		n_flag = 1;
	print_echo(cmd_node, n_flag, STDOUT_FILENO, i_n);
	return (0);
}
