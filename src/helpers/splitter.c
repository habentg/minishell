/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:30:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/05 21:14:31 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	splitter_util(char *str, int *i, int *k, t_quoteType *quote)
{
	while (str[*i] == ' ')
		(*i)++;
	*k = *i;
	if (is_qoute(str[*i]))
	{
		*quote = DOUBLE;
		if (str[*i] == '\'')
			*quote = SINGLE;
		(*i)++;
	}
	while (str[*i] && (*quote != NONE || str[*i] != ' '))
	{
		if (*quote == SINGLE && str[*i] == '\'')
			*quote = NONE;
		else if (*quote == DOUBLE && str[*i] == '\"')
			*quote = NONE;
		else if (*quote == NONE && str[*i] == '\'')
			*quote = SINGLE;
		else if (*quote == NONE && str[*i] == '\"')
			*quote = DOUBLE;
		(*i)++;
	}
	return (*i);
}

char	**splitter(char *str)
{
	char		**res;
	int			i;
	int			k;
	int			res_i;
	t_quoteType	quote;

	i = 0;
	k = i;
	res_i = 0;
	quote = NONE;
	res = (char **)malloc((ft_strlen(str) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		i = splitter_util(str, &i, &k, &quote);
		res[res_i++] = ft_substr(str, k, i - k);
		while (is_whitespace(str[i]))
			i++;
	}
	res[res_i] = NULL;
	return (res);
}

int	ft_strncmp_custom(const char *str1, const char *str2, size_t n)
{
	unsigned int		i;

	i = 0;
	while (str1[i] && i < n)
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	if (str2[i] == '\0' && str1[i] == '\0')
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
