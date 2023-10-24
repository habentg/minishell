/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:30:41 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 03:12:42 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_end_err(t_data **data)
{
	int	i;

	i = (int)(ft_strlen((*data)->input));
	if (i <= 0)
		return (0);
	i = ft_whitespaces((*data)->input, &i, 'b');
	if (i <= 0)
		return (0);
	if ((*data)->input[i] == '|')
		return (ft_error(PIPE_AT_END), 1);
	else if ((*data)->input[i] == '>' || (*data)->input[i] == '<')
		return (ft_error(REDIR_AT_END), 1);
	return (0);
}

static int	open_qoute_err(t_data **data)
{
	bool	flag_s;
	bool	flag_d;
	int		i;

	flag_s = false;
	flag_d = false;
	i = -1;
	while ((*data)->input[++i])
	{
		if ((*data)->input[i] == '\'' && !flag_d)
			flag_s = !flag_s;
		else if ((*data)->input[i] == '\"' && !flag_s)
			flag_d = !flag_d;
	}
	if (flag_s || flag_d)
		return (ft_error(UNCLOSED_QOUTE), 1);
	return (0);
}

int	possible_error(t_data **data)
{
	if (operator_end_err(data))
		return (1);
	if (open_qoute_err(data))
		return (1);
	return (0);
}

int	operator_pipe_error(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (is_operator(token->str[0]) && token->prev == NULL)
			return (0);
		if (token->type == PIPE && is_operator(token->prev->str[0]))
			return (ft_error(OPERATOR_PIPE_ERROR), 1);
		if (is_heredoc_append(token->str, 0, token->str[0]) != 0 \
			&& is_operator(token->prev->str[0]))
		{
			if (is_heredoc_append(token->str, 0, token->str[0]) == 1)
				return (ft_error(OPERATOR_ERROR_HD), 1);
			return (ft_error(OPERATOR_ERROR_APP), 1);
		}
		if (token->type == TRUNC && is_operator(token->prev->str[0]) 
			&& token->prev != NULL)
			return (ft_error(OPERATOR_ERROR_TRU), 1);
		if (is_operator(token->str[0]) && is_operator(token->prev->str[0])\
			&& token->type == INPUT_REDIR && token->prev != NULL)
			return (ft_error(OPERATOR_ERROR_INP), 1);
		token = token->next;
	}
	return (0);
}

void	ft_error(char *err_msg)
{
	ft_putendl_fd(err_msg, 1);
}
