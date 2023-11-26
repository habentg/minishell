/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoutes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:04:14 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/26 16:33:22 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_quote(char c)
{
	int	quote;

	quote = NONE;
	if (c == '\'')
		quote = SINGLE;
	else if (c == '\"')
		quote = DOUBLE;
	return (quote);
}

int	count_len_unqouted(char *str)
{
	int		i;
	int		len;
	int		quote;

	i = 0;
	len = 0;
	quote = NONE;
	while (str && str[i])
	{
		while (!check_quote(str[i]) && str[i] && quote == NONE)
		{
			len++;
			i++;
		}
		if (str[i] && check_quote(str[i]) != NONE)
			quote = check_quote(str[i++]);
		while (str[i] && check_quote(str[i++]) != quote)
			len++;
		if (str[i] && check_quote(str[i]) == quote)
		{
			i++;
			quote = NONE;
		}
	}
	return (len);
}

char	*ft_remove_quotes(char *str, int len)
{
	int		i;
	int		k;
	int		quote;
	char	*tmp;

	i = 0;
	k = 0;
	quote = NONE;
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (NULL);
	while (str && str[i])
	{
		while (!check_quote(str[i]) && str[i] && \
			quote == NONE)
			tmp[k++] = str[i++];
		if (str[i] && check_quote(str[i]) != NONE)
			quote = check_quote(str[i++]);
		while (str[i] && check_quote(str[i]) != quote)
			tmp[k++] = str[i++];
		if (str[i] && check_quote(str[i++]) == quote)
			quote = NONE;
	}
	tmp[k] = '\0';
	return (tmp);
}

void	remove_quotes(t_data *data)
{
	char		*tmp;
	t_token		*token;
	int			len;

	token = data->token;
	while (token)
	{
		len = count_len_unqouted(token->str);
		if (len == (int)ft_strlen(token->str) || \
			(token->prev && token->prev->type == HERE_DOC))
		{
			token = token->next;
			continue ;
		}
		tmp = ft_remove_quotes(token->str, len);
		free(token->str);
		token->str = tmp;
		token = token->next;
	}
}
