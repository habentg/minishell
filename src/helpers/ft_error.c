/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:30:41 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/12 02:31:44 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_end_err(char *input, t_cmd **cmd_list)
{
	size_t	i;

	i = ft_strlen(input) - 1;
	while (input[i] == ' ' || input[i] == '\t')
		i--;
	if (input[i] == '|')
		return (ft_error(PIPE_AT_END, cmd_list), 1);
	else if (input[i] == '>' || input[i] == '<')
		return (ft_error(REDIR_AT_END, cmd_list), 1);
	return (0);
}

static int	open_qoute_err(char *input, t_cmd **cmd_list)
{
	bool	flag_s;
	bool	flag_d;
	int		i;

	flag_s = false;
	flag_d = false;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' && !flag_d)
			flag_s = !flag_s;
		else if (input[i] == '\"' && !flag_s)
			flag_d = !flag_d;
	}
	if (flag_s || flag_d)
		ft_error(UNCLOSED_QOUTE, cmd_list);
	return (flag_s || flag_d);
}

int	possible_error(char *input, t_cmd **cmd_list)
{
	if (operator_end_err(input, cmd_list))
		return (1);
	if (open_qoute_err(input, cmd_list))
		return (1);
	return (0);
}
