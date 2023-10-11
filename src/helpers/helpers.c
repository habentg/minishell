/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:02:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/12 01:05:17 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *err_msg, t_cmd **cmd_list)
{
	ft_putendl_fd(err_msg, 1);
	if (cmd_list)
		ft_clean_dl(cmd_list);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'\
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_whitespaces(char *str, int *index, char c)
{
	int	i;

	i = *index;
	if (c == 'f')
	{
		while (str[++i])
		{
			if (!is_whitespace(str[i]))
				break ;
		}
	}
	else if (c == 'b')
	{
		while (--i >= 0)
		{
			if (!is_whitespace(str[i]))
				break ;
		}	
	}
	return (i);
}
