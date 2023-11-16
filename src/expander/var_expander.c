/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:12:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/17 02:24:38 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_empty_tokens(t_token **token_lst)
{
	t_token	*curr_token;
	t_token	*next_token;

	curr_token = *token_lst;
	while (curr_token)
	{
		if (ft_strncmp_custom(curr_token->str, "", 1) == 0)
		{
			next_token = curr_token->next;
			if (curr_token->prev == NULL)
				*token_lst = next_token;
			else
				curr_token->prev->next = next_token;
			ft_delone_token(curr_token);
			curr_token = next_token;
		}
		else
			curr_token = curr_token->next;
	}
}

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

int	start_expansion(t_data *data)
{
	check_for_var(&data->token);
	init_var_expansion(data);
	remove_empty_tokens(&data->token);
	remove_quotes(data);
	if (!data->token)
		return (1);
	return (0);
}
