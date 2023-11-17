/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:51:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/17 06:45:34 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	wherever is $?, just replace it with exit status
*/

void	expande_exit_status(t_data *data, t_token **token, int i)
{
	char	*tmp;
	char	*tmp_join;
	int		j;
	int		k;
	char	*exit_status_str;

	j = -1;
	k = -1;
	exit_status_str = ft_itoa(data->exit_code);
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

/*
	pretty self explanatory
	> just goes untill a space, operator, {, or qoute is found
*/
int	expande_variable_utils(t_data *data, t_token *token, char *str, int *i)
{
	char	*var_name;
	int		k;

	var_name = NULL;
	if (!str)
		return (-1);
	k = (*i);
	while (str[*i] && !is_whitespace(str[*i]) && str[*i] != '$' \
		&& !is_operator(str[*i]) && !is_qoute(str[*i]) && str[*i] != '{')
				(*i)++;
	if ((*i - k) > 0)
	{
		var_name = ft_substr(token->str, k, *i - k);
		*i = replace_var(data, token, var_name, &k);
		free(var_name);
	}
	return (*i);
}

/*
MOVE THE LAST ELSE PART TO THE expand_variable_utils FUNCTION
	!! when you find $
		> if the next char is a ? then expand the exit status
			* follow the function expande_exit_status
		> or untill a space, operator, or qoute is found will considered var_name
			* follow the function expande_variable_utils
		> then we send var_name to be searched and replaced with the value
			* follow the function replace_var
*/
void	expand_variable(t_data *data, t_token *token)
{
	int		i;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$' && get_q_state(token->str, i) != SINGLE)
		{
			if (token->str[++i] == '?')
				expande_exit_status(data, &token, i);
			else
			{
				i = expande_variable_utils(data, token, token->str, &i);
				if (i == -1)
					break ;
			}
			i = -1;
		}
		i++;
	}
}
