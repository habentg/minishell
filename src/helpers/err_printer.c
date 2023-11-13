/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:52:48 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/13 05:34:44 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_error_2(char *s1, char *s2, char *s3, int exit_status)
{
	g_exit_status = exit_status;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s3, 2);
	ft_putstr_fd("\n", 2);
}

void	display_error(char *s1, char *s2, int exit_status)
{
	g_exit_status = exit_status;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_error(char *err_msg, int exit_status)
{
	g_exit_status = exit_status;
	ft_putendl_fd(err_msg, 2);
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

char	**ft_split_custom(char *str)
{
	int		i;
	char	**res;

	if (!str)
		return (NULL);
	i = 0;
	res = ft_calloc(3, sizeof(char *));
	if (!res)
		return (NULL);
	if (ft_strchr(str, '=') == NULL)
	{
		res[0] = ft_strdup(str);
		return (res);
	}
	while (str[i] != '=')
		i++;
	res[0] = ft_substr(str, 0, ++i);
	if (str[i] == '\0')
		return (res);
	res[1] = ft_substr(str, i, ft_strlen(str));
	return (res);
}
