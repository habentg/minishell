/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:12:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/16 15:47:10 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_var_expansion(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			pid_replacer(tmp);
			if (is_expansion_possible(tmp->str, tmp->type))
			{
				expand_variable(data, tmp);
				tmp->type = WORD;
			}
			else
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
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

void	start_expansion(t_data *data)
{
	check_for_var(&data->token);
	init_var_expansion(data);
	remove_quotes(data);
}
