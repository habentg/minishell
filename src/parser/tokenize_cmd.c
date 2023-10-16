/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:57:50 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/16 18:09:20 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	splited_count(char const *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

char	*clip_qouted(char *str, int *i)
{
	char	c;
	int		k;
	char	*s;
	int		r;

	k = *i;
	r = -1;
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

char	*clip_normal(char *cmd, int *i)
{
	int	k;

	k = *i;
	while (cmd[*i] != ' ' && cmd[*i] != '\0')
		(*i)++;
	return (ft_substr(cmd, k, ((*i) - k + 1)));
}

char	**get_members(char *cmd)
{
	char	**res;
	int		i;
	int		z;
	int		size;
	int		end;

	z = -1;
	i = -1;
	size = ft_strlen(cmd);
	i = ft_whitespaces(cmd, &i, 'f');
	end = ft_whitespaces(cmd, &size, 'b');
	res = (char **)ft_calloc(sizeof(char *), splited_count(cmd, 32) + 1);
	while (i < (end + 1))
	{
		while (cmd[i] == ' ' && cmd[i] != '\0')
			i++;
		if (is_qoute(cmd[i]))
		{
			res[++z] = clip_qouted(cmd, &i);
			i++;
		}
		else
			res[++z] = clip_normal(cmd, &i);
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
	printf("cmd: [%s]\n", cmd);
	mem_arr = get_members(cmd);
	i = -1;
	arr_size = arr_length(mem_arr);
	printf("-arr_size: %d\n", arr_size);
	while (mem_arr[++i] != NULL)
	{
		token = tokenize_mem(mem_arr[i], 0);
		free(mem_arr[i]);
		printf("    ~>token: %s, type: %u\n", token->str, token->type);
		if (add_tok_back(token_lst, token, 0))
			break ;
	}
	printf("dl size: %d\n", ft_tokendl_size(token_lst));
	free(mem_arr);
}
	// t_token	*tmp;
	// tmp = *token_lst;
	// while (tmp)
	// {
	// 	printf("    ~>token: %s, type: %u\n", tmp->str, tmp->type);
	// 	tmp = tmp->next;
	// }
