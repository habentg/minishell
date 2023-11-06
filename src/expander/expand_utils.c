/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:49:37 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 18:47:23 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quoteType	get_q_state(char *str, int end)
{
	int			i;
	t_quoteType	quote;

	quote = NONE;
	i = 0;
	while (i < end)
	{
		if (quote == SINGLE && str[i] == '\'')
			quote = NONE;
		else if (quote == DOUBLE && str[i] == '\"')
			quote = NONE;
		else if (quote == NONE && str[i] == '\'')
			quote = SINGLE;
		else if (quote == NONE && str[i] == '\"')
			quote = DOUBLE;
		i++;
	}
	return (quote);
}

int	is_expansion_possible(char *str)
{
	int			i;
	t_quoteType	quote;

	quote = NONE;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '$')
				return (ft_error("Error: Double $"), 2);
			quote = get_q_state(str, i);
			if (quote != SINGLE)
				return (1);
		}
		i++;
	}
	return (0);
}
