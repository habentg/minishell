/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:49:37 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/17 06:48:42 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quoteType	get_q_state(char *str, int end)
{
	int			i;
	t_quoteType	quote;

	quote = NONE;
	i = 0;
	while (i < end)
	{
		if (quote == SINGLE && str[i] == '\'')
			quote = NONE;
		else if (quote == DOUBLE && str[i] == '\"')
			quote = NONE;
		else if (quote == NONE && str[i] == '\'')
			quote = SINGLE;
		else if (quote == NONE && str[i] == '\"')
			quote = DOUBLE;
		i++;
	}
	return (quote);
}

char	*replace_double_var(t_token *token, int *i)
{
	char	*b_var;
	char	*a_var;
	char	*final_join;
	char	*not_final_join;

	b_var = ft_substr(token->str, 0, *i);
	if (!b_var)
		b_var = NULL;
	a_var = ft_substr(token->str, *i + 2, ft_strlen(token->str));
	if (!a_var)
		a_var = NULL;
	if (!b_var)
		not_final_join = ft_strdup("{PID}");
	else
		not_final_join = var_not_found(b_var, "{PID}", i);
	if (!a_var)
		final_join = ft_strdup(not_final_join);
	else
		final_join = ft_strjoin(not_final_join, a_var);
	*i = ft_strlen(not_final_join);
	free(b_var);
	free(a_var);
	free(not_final_join);
	return (final_join);
}

void	pid_replacer(t_token *token)
{
	int			i;
	t_quoteType	quote;
	char		*tmp_str;

	quote = NONE;
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$')
		{
			quote = get_q_state(token->str, i);
			if (token->str[i + 1] && token->str[i + 1] == '$' \
				&& quote != SINGLE)
			{
				tmp_str = replace_double_var(token, &i);
				free(token->str);
				token->str = tmp_str;
				i = -1;
			}
		}
		i++;
	}
}

bool	is_expansion_possible(char *str, int t_type)
{
	int			i;
	t_quoteType	quote;

	quote = NONE;
	i = 0;
	if (t_type == WORD)
		return (false);
	while (str[i])
	{
		if (str[i] == '$')
		{
			quote = get_q_state(str, i);
			if (quote != SINGLE)
				return (true);
		}
		i++;
	}
	return (false);
}
