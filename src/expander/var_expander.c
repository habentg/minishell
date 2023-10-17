/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:12:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 21:40:33 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	// count the number of chars in the var
	// ft_strncmp with the envp
	// if match, replace(ft_srdup) the var with the value of the envp (after equal)

	1. loop 
	2 if var
		 call a funcion to check if expansion is possible (if yes)
		 	var_expander
				get the value of the var
				replace the var with the value (rplace the string do not forget to free the old string)
		if not possible
			continue;
	3. if not var 
		continue;
*/

static void	expand_variable(t_data *data, t_token *token)
{
	(void)data;
	(void)token;
}

static int	is_expansion_possible(t_data *data, t_token *token)
{
	(void)data;
	(void)token;
	return (0);
}

static void	expand_var(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == VAR)
			if (is_expansion_possible(data, tmp))
				expand_variable(data, tmp);
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
		{
			tmp->type = VAR;
		}
		tmp = tmp->next;
	}
}

int	start_expansion(t_data *data)
{
	check_for_var(&data->token);
	expand_var(data);
	return (0);
}
