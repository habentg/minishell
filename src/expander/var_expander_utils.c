/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:51:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/03 07:15:17 by hatesfam         ###   ########.fr       */
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

void	remove_var_sign(t_token *token, int i)
{
	char	*before_var;
	char	*after_var;
	char	*final_value;

	before_var = ft_substr(token->str, 0, (i - 1));
	if (!before_var)
		before_var = NULL;
	after_var = ft_substr(token->str, i, ft_strlen(token->str));
	if (!after_var)
		after_var = NULL;
	final_value = var_not_found(&token, before_var, after_var);
	free(token->str);
	token->str = final_value;
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
	if (!str || !token || str[*i] == '\0')
		return (-1);
	k = (*i);
	while (str[*i] && !is_whitespace(str[*i]) && str[*i] != '$' \
		&& !is_operator(str[*i]) && !is_qoute(str[*i]) && str[*i] != '{')
		(*i)++;
	if (*i == k)
		return (-1);
	var_name = ft_substr(token->str, k, *i - k);
	if (!var_name)
		return (-1);
	*i = replace_var(data, &token, var_name, &k);
	if (var_name)
		free(var_name);
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
			if (token->str[i + 1] == '\0')
				break ;
			if (is_qoute(token->str[++i]) && \
				get_q_state(token->str, (i - 1)) == NONE)
				remove_var_sign(token, i);
			else if (token->str[i] == '?')
				expande_exit_status(data, &token, i);
			else
			{
				i = expande_variable_utils(data, token, token->str, &i);
				if (!token->str || i == -1)
					break ;
			}
			i = -1;
		}
		i++;
	}
}
