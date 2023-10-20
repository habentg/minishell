/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combination_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:15:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/19 17:40:55 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	operator_pipe_error(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (token->type == PIPE && token->prev->type == PIPE)
			return (ft_error(OPERATOR_PIPE_ERROR, &data), 1);
		else if (token->type == PIPE && token->prev->type == APPEND)
			return (ft_error(OPERATOR_PIPE_ERROR, &data), 1);
		else if (token->type == PIPE && token->prev->type == TRUNC)
			return (ft_error(OPERATOR_PIPE_ERROR, &data), 1);
		else if (token->type == PIPE && token->prev->type == INPUT_REDIR)
			return (ft_error(OPERATOR_PIPE_ERROR, &data), 1);
		else if (token->type == PIPE && token->prev->type == HERE_DOC)
			return (ft_error(OPERATOR_PIPE_ERROR, &data), 1);
		token = token->next;
	}
	return (0);
}
