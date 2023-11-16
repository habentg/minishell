/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:34:15 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/16 12:53:59 by hatesfam         ###   ########.fr       */
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

bool	fits_in_longlong(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (false);
	if (ft_strncmp_custom("-9223372036854775808", str, ft_strlen(str)) == 0)
		return (true);
	out = 0;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (false);
		out = out * 10 + c;
		str += 1;
	}
	return (true);
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
	if (!fits_in_longlong(str))
		return (0);
	return (1);
}

int	handle_exit(t_data *data, t_cmd *cmd_node)
{
	shlvl_increment(data, 0);
	if (arr_length(cmd_node->cmdarg) == 1)
		data->exit_code = 0;
	else if (arr_length(cmd_node->cmdarg) == 2)
	{
		if (!valid_e_status(cmd_node->cmdarg[1]))
		{
			data->exit_code = 255;
			display_error_2("exit", cmd_node->cmdarg[1], \
				"numeric argument required", 255);
		}
		else
		{
			data->exit_code = ft_atol(cmd_node->cmdarg[1]) % 256;
			if (ft_atol(cmd_node->cmdarg[1]) < 0)
				data->exit_code = 256 + data->exit_code;
		}
	}
	else if (arr_length(cmd_node->cmdarg) > 2)
	{
		data->exit_code = 1;
		return (display_error("exit", "too many arguments", 1), 1);
	}
	ft_clean_data_done(&data, 1);
	exit(data->exit_code);
}
