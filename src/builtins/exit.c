/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:34:15 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/12 18:35:31 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_sign(char c)
{
	if (c == '-')
		return (-1);
	else if (c == '+')
		return (1);
	return (0);
}

// int ft_isdigit_custom()
int	valid_e_status(char *str)
{
	int		i;
	int		j;
	int		sign;

	i = -1;
	j = ft_strlen(str);
	i = ft_whitespaces(str, &i, 'f');
	j = ft_whitespaces(str, &j, 'b');
	sign = set_sign(str[i]);
	if (sign != 0)
		i++;
	while (str[i] && i <= j)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if ((ft_strlen(str) > 20 || (sign == 1 && ft_atol(str) < 0)) \
			|| (sign == -1 && ft_atol(str) > 0))
		return (0);
	return (1);
}

int	handle_exit(t_data *data, t_cmd *cmd_node)
{
	shlvl_increment(data, 0);
	if (arr_length(cmd_node->cmdarg) == 1)
	{
		ft_clean_data_done(&data, 1);
		exit(0);
	}
	else
	{
		g_exit_status = 1;
		if (!valid_e_status(cmd_node->cmdarg[1]))
		{
			display_error_2("exit", "numeric argument required", 255);
			ft_clean_data_done(&data, 1);
			exit(255);
		}
		else if (cmd_node->cmdarg[2])
			return (display_error_2("exit", "too many arguments", 1), 1);
		g_exit_status = ft_atol(cmd_node->cmdarg[1]) % 256;
		if (ft_atol(cmd_node->cmdarg[1]) < 0)
			g_exit_status = 256 + g_exit_status;
		ft_clean_data_done(&data, 1);
		exit(g_exit_status);
	}
	return (0);
}
