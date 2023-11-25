/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_space_setter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:57:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/25 23:33:45 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	osc_helper_quotes(char *str, int *i, int *res)
{
	(*res)++;
	while (1)
	{
		if (is_qoute(str[*i]))
		{
			if (str[*i + 1] && is_qoute(str[*i + 1]))
			{
				(*i)++;
				continue ;
			}
			if (!str[*i + 1] || (str[*i + 1] && ((is_whitespace(str[*i + 1]) || \
				is_operator(str[*i + 1])) && get_q_state(str, *i + 1) == NONE)))
			{
				(*i)++;
				break ;
			}
		}
		(*i)++;
	}
}

static void	osc_helper_operator(char *str, int *i, int *res)
{
	(*res)++;
	if (str[*i] && is_operator(str[*i]))
	{
		if (str[*i] && str[*i] == '>' && str[*i + 1] == '>')
			(*i)++;
		else if (str[*i] && str[*i] == '<' && str[*i + 1] == '<')
			(*i)++;
		(*i)++;
	}
}

static void	osc_helper_default(char *str, int *i, int *res)
{
	(*res)++;
	while (1)
	{
		if (!str[*i] || (str[*i] && (is_operator(str[*i]) || \
			is_whitespace(str[*i])) && get_q_state(str, *i) == NONE))
			break ;
		(*i)++;
	}
}

int	one_space_counter(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		if (is_qoute(str[i]))
			osc_helper_quotes(str, &i, &res);
		else if (str[i] && is_operator(str[i]))
			osc_helper_operator(str, &i, &res);
		else
			osc_helper_default(str, &i, &res);
	}
	return (res);
}

void	helper_quotes(char ***arr, char *str, int *i, int *arr_i)
{
	int	k;

	k = *i;
	while (1)
	{
		if (is_qoute(str[*i]))
		{
			if (str[*i + 1] && is_qoute(str[*i + 1]))
			{
				(*i)++;
				continue ;
			}
			if (!str[*i + 1] || (str[*i + 1] && ((is_whitespace(str[*i + 1]) || \
				is_operator(str[*i + 1])) && get_q_state(str, *i + 1) == NONE)))
			{
				(*i)++;
				break ;
			}
		}
		(*i)++;
	}
	(*arr)[(*arr_i)++] = ft_substr(str, k, *i - k);
}
