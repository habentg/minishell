/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:51:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 18:51:20 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_var_utils(char *str, char *envi, int varlen, int *k)
{
	char	*tmp;
	int		remain_len;

	tmp = NULL;
	remain_len = (int)ft_strlen(str) - varlen - 1;
	tmp = (char *)ft_calloc(sizeof(char), (remain_len + \
		((int)ft_strlen(envi) - varlen - 1) + 1));
	while (str[*k])
	{
		if (str[*k] == '$' && get_q_state(str, *k) != SINGLE)
			break ;
		tmp[*k] = str[*k];
		(*k)++;
	}
	return (tmp);
}

void	expande_exit_status(t_token **token, int i)
{
	char	*tmp;
	char	*tmp_join;
	int		j;
	int		k;
	char	*exit_status_str;

	j = -1;
	k = -1;
	exit_status_str = ft_itoa(g_exit_status);
	tmp = (char *)ft_calloc(sizeof(char), ((ft_strlen((*token)->str)) - 2 + \
		(ft_strlen(exit_status_str) + 1)));
	if (!tmp)
		return ;
	while (++j < (i - 1))
		tmp[j] = (*token)->str[j];
	tmp_join = ft_strdup(exit_status_str);
	while (tmp_join[++k])
		tmp[j++] = tmp_join[k];
	while ((*token)->str[++i])
		tmp[j++] = (*token)->str[i];
	free(tmp_join);
	free((*token)->str);
	(*token)->str = tmp;
	free(exit_status_str);
}

int	replace_var(t_data *data, t_token *token, char *var_name, int *index)
{
	int		i;
	int		k;
	int		remain_index;
	int		var_len;
	char	*tmp;

	i = -1;
	k = 0;
	remain_index = 0;
	var_len = (int)ft_strlen(var_name);
	tmp = NULL;
	while (data->envi[++i])
	{
		if (ft_strncmp(data->envi[i], var_name, var_len) == 0)
		{
			tmp = replace_var_utils(token->str, data->envi[i], var_len, &k);
			remain_index = k + var_len + 1;
			while (data->envi[i][++var_len])
				tmp[k++] = data->envi[i][var_len];
			*index = k;
			while (token->str[remain_index])
				tmp[k++] = token->str[remain_index++];
			free(token->str);
			token->str = tmp;
		}
	}
	return (*index);
}

static int	expande_variable_utils(char *str, int *i)
{
	while (str[*i] && !is_whitespace(str[*i]) && str[*i] != '$' \
		&& !is_operator(str[*i]) && !is_qoute(str[*i]))
				(*i)++;
	return (*i);
}

void	expand_variable(t_data *data, t_token *token)
{
	char	*var_name;
	int		i;
	int		k;

	var_name = NULL;
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$' && get_q_state(token->str, i) != SINGLE)
		{
			k = ++i;
			if (token->str[i] == '?')
			{
				expande_exit_status(&token, i);
				i = 0;
				continue ;
			}
			if (!token->str[i])
				break ;
			i = expande_variable_utils(token->str, &i);
			if ((i - k) > 0)
			{
				var_name = ft_substr(token->str, k, i - k);
				i = replace_var(data, token, var_name, &i);
				free(var_name);
			}
		}
		else
			i++;
	}
}
