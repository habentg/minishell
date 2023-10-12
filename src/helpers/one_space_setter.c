/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_space_setter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:25:50 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/12 13:18:35 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_heredoc_append(char *str, int i, char c)
{
	if (str[i + 1] == c)
		return (1);
	return (0);
}

int	is_qoute(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

static char	*sett(char *str, char *res, int start, int end)
{
	int	i;
	int	q;

	i = -1;
	while (start <= (end + 1))
	{
		if (is_whitespace(str[start]))
		{
			res[++i] = ' ';
			start = ft_whitespaces(str, &start, 'f');
		}
		if (is_qoute(str[start]))
		{
			q = start;
			res[++i] = str[q];
			while (str[++q] != str[start])
				res[++i] = str[q];
			start = q;
		}
		else if (is_operator(str[start]))
		{
			if (i != -1 && !is_operator(res[i]) && !is_whitespace(res[i]))
				res[++i] = ' ';
			res[++i] = str[start];
			if (is_heredoc_append(str, start, str[start]))
				res[++i] = str[start++];
			res[++i] = ' ';
			start = ft_whitespaces(str, &start, 'f');
		}
		else
			res[++i] = str[start++];
	}
	res[i] = '\0';
	return (res);
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
	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	return (sett(str, res, start, end));
}
