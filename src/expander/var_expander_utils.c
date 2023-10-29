/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:51:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/30 00:03:05 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	search_n_replace()
// {

// }

int	replace_var(t_data *data, t_token *token, char *var_name, int *index)
{
	int		i;
	int		k;
	int		remain_len;
	int		var_len;
	char	*tmp;

	i = -1;
	k = 0;
	remain_len = 0;
	var_len = (int)ft_strlen(var_name);
	tmp = NULL;
	while (data->envi[++i])
	{
		if (ft_strncmp(data->envi[i], var_name, var_len) == 0)
		{
			remain_len = ft_strlen(token->str) - var_len - 1;
			tmp = (char *)malloc(sizeof(char) * (remain_len + \
				(ft_strlen(data->envi[i]) - var_len - 1) + 1));
			while (token->str[k])
			{
				if (token->str[k] == '$' && get_q_state(token->str, k) \
					!= SINGLE)
					break ;
				tmp[k] = token->str[k];
				k++;
			}
			remain_len = k + var_len + 1;
			while (data->envi[i][++var_len])
				tmp[k++] = data->envi[i][var_len];
			*index = k;
			while (token->str[remain_len])
				tmp[k++] = token->str[remain_len++];
			tmp[k] = '\0';
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
