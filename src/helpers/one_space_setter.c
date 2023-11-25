/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_space_setter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:57:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/25 20:23:25 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	one_space_counter(char *str)
{
	int	res = 0;
	int	i = 0;

	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		if (is_qoute(str[i]))
		{
			res++;
			while (1)
			{
				if (is_qoute(str[i]))
				{
					if (str[i + 1] && is_qoute(str[i + 1]))
					{
						i++;
						continue ;
					}
					if (!str[i + 1] || (str[i + 1] && ((is_whitespace(str[i + 1]) || is_operator(str[i+1])) && get_q_state(str, i+1) == NONE)))
					{
						i++;
						break ;
					}
				}
				i++;
			}
		}
		else if (str[i] && is_operator(str[i]))
		{
			res++;
			if (str[i] && str[i] == '>' && str[i + 1] == '>')
				i++;
			else if (str[i] && str[i] == '<' && str[i + 1] == '<')
				i++;
			i++;
		}
		else
		{
			res++;
			while (1)
			{
				if (!str[i] || (str[i] && (is_operator(str[i]) || \
					is_whitespace(str[i])) && get_q_state(str, i) == NONE))
					break ;
				i++;
			}
		}
	}
	return (res);
}
