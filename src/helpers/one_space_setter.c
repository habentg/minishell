/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_space_setter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:57:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/16 12:23:34 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_qouted(char *str, int *j, char **res, int *res_i)
{
	int	qoute_type;

	qoute_type = str[*j];
	(*res)[(*res_i)++] = str[*j];
	(*j)++;
	while (str[*j] && str[*j] != qoute_type)
		(*res)[(*res_i)++] = str[(*j)++];
	if (str[*j])
		(*res)[(*res_i)++] = str[(*j)++];
}

void	handle_operator(char *str, int *j, char **res, int *res_i)
{
	char	operator_type;

	operator_type = str[*j];
	(*res)[(*res_i)++] = ' ';
	(*res)[(*res_i)++] = str[*j];
	(*j)++;
	if (operator_type == str[*j])
		(*res)[(*res_i)++] = str[(*j)++];
	(*res)[(*res_i)++] = ' ';
}

static void	sett(char *str, char **res, int j, int k)
{
	int	res_i;

	res_i = 0;
	while (j < (k + 1))
	{
		if (is_whitespace(str[j]))
		{
			(*res)[res_i++] = ' ';
			while (is_whitespace(str[j]))
				j++;
		}
		if (is_qoute(str[j]))
			handle_qouted(str, &j, res, &res_i);
		if (is_operator(str[j]))
			handle_operator(str, &j, res, &res_i);
		else
			(*res)[res_i++] = str[j++];
	}
	(*res)[res_i] = '\0';
}

char	*one_space_setter(char *str)
{
	int		i;
	int		start;
	int		end;
	int		str_size;
	char	*res;

	i = -1;
	str_size = (int)ft_strlen(str);
	start = ft_whitespaces(str, &i, 'f');
	end = ft_whitespaces(str, &str_size, 'b');
	res = NULL;
	if (!str)
		return (NULL);
	res = (char *)malloc(sizeof(char) * 200);
	if (!res)
		return (NULL);
	sett(str, &res, start, end);
	return (res);
}