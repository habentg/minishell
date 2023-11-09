/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:34:15 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/09 20:51:38 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_e_status(char *str)
{
	int		i;
	int		j;
	int		sign;

	i = -1;
	sign = 1;
	j = ft_strlen(str);
	i = ft_whitespaces(str, &i, 'f');
	j = ft_whitespaces(str, &i, 'b');
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (i <= j)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	// not working for less than llong min
	if ((sign == 1 && ft_atol(str) < 0) || (sign == -1 && ft_atol(str) > 0))
		return (0);
	return (1);
}

int	handle_exit(t_data *data, t_cmd *cmd_node)
{
	printf("exit\n");
	if (arr_length(cmd_node->cmdarg) == 1)
	{
		ft_clean_data_done(&data);
		exit(0);
	}
	else
	{
		g_exit_status = 1;
		if (!valid_e_status(cmd_node->cmdarg[1]))
		{
			printf("Error: exit: %s: numeric argument required\n", \
				cmd_node->cmdarg[1]);
			ft_clean_data_done(&data);
			exit(255);
		}
		else if (cmd_node->cmdarg[2])
			return (display_error_2("exit", "too many arguments", 1), 1);
		g_exit_status = ft_atol(cmd_node->cmdarg[1]) % 256;
		if (ft_atol(cmd_node->cmdarg[1]) < 0)
			g_exit_status = 256 + g_exit_status;
		ft_clean_data_done(&data);
		exit(g_exit_status);
	}
	return (0);
}
