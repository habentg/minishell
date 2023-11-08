/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 02:34:15 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/08 20:49:48 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_digit_custom(char *str)
{
	int	i;
	int	j;

	i = -1;
	i = ft_whitespaces(str, &i, 'f');
	j = ft_strlen(str);
	j = ft_whitespaces(str, &j, 'b');
	while (i <= j)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (ft_atoi(str) > 255)
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
		if (!is_digit_custom(cmd_node->cmdarg[1]))
		{
			printf("Error: exit: %s: numeric argument required\n", \
				cmd_node->cmdarg[1]);
			ft_clean_data_done(&data);
			exit(255);
		}
		else if (cmd_node->cmdarg[2])
		{
			g_exit_status = ft_atoi(cmd_node->cmdarg[1]);
			return (printf("Error: exit: too many arguments\n"), g_exit_status);
		}
		ft_clean_data_done(&data);
		exit(ft_atoi(cmd_node->cmdarg[1]));
	}
	return (0);
}
