/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:57:50 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/14 21:38:55 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*clip_qouted(char *str, int *i)
{
	char	c;
	int		k;
	int		j;
	char	*s;
	int		r;

	k = *i;
	r = -1;
	j = k;
	c = str[k++];
	s = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	s[++r] = c;
	while (c != str[k] && str[k] != '\0')
		s[++r] = str[k++];
	s[++r] = str[k];
	s[++r] = c;
	s[r] = '\0';
	*i = k;
	return (s);
}

char	**get_members(char *cmd)
{
	char	**res;
	int		i;
	int		k;
	int		z;

	z = -1;
	i = 0;
	k = 0;
	res = (char **)ft_calloc(sizeof(char *), 100);
	while (cmd[i])
	{
		while (cmd[i] == ' ' && cmd[i] != '\0')
			i++;
		if (is_qoute(cmd[i]))
		{
			res[++z] = clip_qouted(cmd, &i);
			i++;
		}
		else
		{
			k = i;
			while (cmd[i] != ' ' && cmd[i] != '\0')
				i++;
			res[++z] = ft_substr(cmd, k, (i - k + 1));
		}
	}
	return (res);
}

void	tokenize_cmd(t_token **token_lst, char *cmd)
{
	char	**mem_arr;
	int		i;
	int		arr_size;
	t_token	*token;

	i = -1;
	printf("~>[%s]\n", cmd);
	mem_arr = get_members(cmd);
	i = -1;
	arr_size = arr_length(mem_arr);
	while (mem_arr[++i] != NULL)
	{
		token = tokenize_mem(mem_arr[i], 0);
		free(mem_arr[i]);
		printf("    ~>token: %s, type: %u\n", token->str, token->type);
		if (add_tok_back(token_lst, token, 0))
			break ;
	}
}
