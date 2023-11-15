/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:51:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/15 09:52:57 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	expande_variable_utils(char *str, int *i)
{
	while (str[*i] && !is_whitespace(str[*i]) && str[*i] != '$' \
		&& !is_operator(str[*i]) && !is_qoute(str[*i]) && str[*i] != '{')
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
				i = replace_var(data, token, var_name, &k);
				free(var_name);
			}
		}
		else
			i++;
	}
}
