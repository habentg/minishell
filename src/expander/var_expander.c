/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:12:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/23 20:10:00 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	after var expansion, remove any empty tokens
	they are useless
*/
static void	remove_empty_tokens(t_token **token_lst)
{
	t_token	*curr_token;
	t_token	*next_token;

	curr_token = *token_lst;
	while (curr_token)
	{
		if (ft_strncmp_custom(curr_token->str, "", 1) == 0 \
			&& curr_token->was_mpty_before == 0)
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

/*
	when type is var, check if it is a valid variable
		* replace $$ with {PID}, would expand it to the pid, getpid() is forbiden
		* $ in single quotes is not a variable
		* $ in double quotes && without qoutes is a variable
	$ if expandable
		* FOLLOW ME TO EXPAND_VARIABLE
		* change the type to WORD
	$ else
		* change the type to WORD
		
*/
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

/*
	~ if it has a $ in it, must be a var
*/
static void	check_for_var(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '$'))
		{
			tmp->type = VAR;
			if (tmp->prev && tmp->prev->type == HERE_DOC)
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}

int	check_after_del(t_data *data, t_token *token)
{
	if (last_mem(token)->type == PIPE)
		return (1);
	if (is_token_operator(last_mem(token)))
	{
		data->exit_code = 1;
		return (display_error("--", "ambiguous redirect"), 1);
	}
	return (0);
}

/*
	VAR EXPANSION
	~ expand the variable
	~ remove any empty tokens (happens after $INVALID_VAR)
	~ remove extra qoutes 
	~ if !token_lst return 1 and I dont have to proced with command extration	
*/
int	start_expansion(t_data *data)
{
	if (!data || !data->token)
		return (1);
	check_for_var(&data->token);
	init_var_expansion(data);
	remove_quotes(data);
	remove_empty_tokens(&data->token);
	if (!data->token)
		return (1);
	if (check_after_del(data, data->token))
		return (1);
	return (0);
}
