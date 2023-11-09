/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:52:48 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/09 20:19:18 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	file_dir_not_found(char *dir)
{
	g_exit_status = 1;
	printf("minishell: cd: %s: No such file or directory\n", dir);
}

void	display_error_2(char *s1, char *s2, int exit_status)
{
	g_exit_status = exit_status;
	printf("minishell: %s: %s\n", s1, s2);
}

void	ft_error(char *err_msg, int exit_status)
{
	g_exit_status = exit_status;
	ft_putendl_fd(err_msg, 1);
}

long	ft_atol(char *str)
{
	int		i;
	long	number;
	int		sign;

	i = -1;
	number = 0;
	sign = 1;
	i = ft_whitespaces(str, &i, 'f');
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}
