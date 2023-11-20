/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:30:41 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/20 20:09:52 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	removes whitespaces from the back 
	and checks if there is a pipe or redirection
*/
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
		return (ft_error(*data, PIPE_AT_END, 258), 1);
	else if ((*data)->input[i] == '>' || (*data)->input[i] == '<')
		return (ft_error(*data, REDIR_AT_END, 258), 1);
	return (0);
}

/*
	checks if there is an unclosed quote i.e
	~ ' or " thats not closed or inside a quote that has a closing quote
*/
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
		return (ft_error(*data, UNCLOSED_QOUTE, 258), 1);
	return (0);
}

/*
	checks if there is an error in the input
	~ if there is an operator at the end
	~ if there is an unclosed quote
*/
int	possible_error(t_data **data)
{
	if (!data || !(*data)->input)
		return (0);
	if (operator_end_err(data))
		return (1);
	if (open_qoute_err(data))
		return (1);
	return (0);
}

/*
	if its redirection
*/
int	is_token_operator(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == APPEND || token->type == TRUNC \
		|| token->type == INPUT_REDIR || token->type == HERE_DOC)
		return (1);
	return (0);
}

/*
	handles pipe - redirection && redirection - redirection combination errors
	?? shit is exausting, had to manually check all the possible lmao
*/
int	operator_pipe_error(t_data *data)
{
	t_token	*token;

	token = data->token;
	if (ft_tokendl_size(&token) == 1 && (is_token_operator(token)))
		return (ft_error(data, REDIR_AT_END, 258), 1);
	while (token)
	{
		if (token->type == PIPE && ((!token->next)))
			return (ft_error(data, OPERATOR_PIPE_ERROR, 258), 1);
		if (is_token_operator(token) && (!token->next))
			return (ft_error(data, REDIR_AT_END, 258), 1);
		if (token->type == PIPE && (is_token_operator(token->prev) \
			|| token == data->token || token->next->type == PIPE))
			return (ft_error(data, OPERATOR_PIPE_ERROR, 258), 1);
		if (is_token_operator(token) && token->next->type == HERE_DOC)
			return (ft_error(data, OPERATOR_ERROR_HD, 258), 1);
		if (is_token_operator(token) && token->next->type == APPEND)
			return (ft_error(data, OPERATOR_ERROR_APP, 258), 1);
		if (is_token_operator(token) && token->next->type == TRUNC)
			return (ft_error(data, OPERATOR_ERROR_TRU, 258), 1);
		if (is_token_operator(token) && token->next->type == INPUT_REDIR)
			return (ft_error(data, OPERATOR_ERROR_INP, 258), 1);
		token = token->next;
	}
	return (0);
}
