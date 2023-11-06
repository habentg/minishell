/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:12:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 18:49:08 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_var_expansion(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			if (is_expansion_possible(tmp->str) != 0)
			{
				if (is_expansion_possible(tmp->str) == 2)
					return (1);
				expand_variable(data, tmp);
				tmp->type = WORD;
			}
			else
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	check_for_var(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (tmp)
	{
		if (strchr(tmp->str, '$'))
			tmp->type = VAR;
		tmp = tmp->next;
	}
}

int	start_expansion(t_data *data)
{
	check_for_var(&data->token);
	if (init_var_expansion(data))
		return (1);
	remove_quotes(data);
	return (0);
}
