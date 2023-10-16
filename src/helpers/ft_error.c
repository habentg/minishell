/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:30:41 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/16 17:59:40 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_end_err(char *input, t_cmd **cmd_list)
{
	int	i;

	i = (int)(ft_strlen(input));
	if (i <= 0)
		return (0);
	i = ft_whitespaces(input, &i, 'b');
	if (i <= 0)
		return (0);
	while (is_whitespace(input[i]))
		if (i == 0)
			return (0);
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

void	ft_error(char *err_msg, t_cmd **cmd_list)
{
	ft_putendl_fd(err_msg, 1);
	if (cmd_list)
		ft_clean_dl(cmd_list);
}
