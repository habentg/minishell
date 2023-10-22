/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:30:41 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/22 12:23:46 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_end_err(char *input)
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
		return (ft_error(PIPE_AT_END, NULL), 1);
	else if (input[i] == '>' || input[i] == '<')
		return (ft_error(REDIR_AT_END, NULL), 1);
	return (0);
}

static int	open_qoute_err(char *input)
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
		return (ft_error(UNCLOSED_QOUTE, NULL), 1);
	return (0);
}

int	possible_error(char *input)
{
	if (operator_end_err(input))
		return (1);
	if (open_qoute_err(input))
		return (1);
	return (0);
}

void	ft_error(char *err_msg, t_data **data)
{
	ft_putendl_fd(err_msg, 1);
	if (data)
		ft_clean_data(data);
}


int	operator_pipe_error(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (token->type == PIPE && token->prev->type == PIPE)
			return (ft_error(OPERATOR_PIPE_ERROR, &data), 1);
		else if (token->type == PIPE && is_operator(token->prev->str[0]))
			return (ft_error(OPERATOR_ERROR, &data), 1);
		else if (is_operator(token->str[0]) && is_operator(token->prev->str[0]))
			return (ft_error(OPERATOR_ERROR, &data), 1);
		token = token->next;
	}
	return (0);
}
			