/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:53:39 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/16 20:20:17 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	remove_empty_token(t_token *token_lst, t_token *token)
// {
// 	t_token	*t_node;

// 	t_node = token_lst;
// 	while (t_node->next)
// 	{
// 		if (t_node->next == token)
// 		{
// 			if (t_node)
// 			t_node->prev = token->next;
// 			free(token->str);
// 			free(token);
// 			return ;
// 		}
// 		t_node = t_node->next;
// 	}
// }

void	free_allocs(char *varname_tmp, char *before_var, \
	char *after_var, char *path_join)
{
	free(varname_tmp);
	free(before_var);
	free(after_var);
	if (path_join)
		free(path_join);
}

char	*var_not_found(char *b_var, char *a_var, int *index)
{
	char	*final_join;

	if (!b_var)
		final_join = ft_strdup(a_var);
	else if (!a_var)
		final_join = ft_strdup(b_var);
	else
		final_join = ft_strjoin(b_var, a_var);
	*index = ft_strlen(b_var);
	return (final_join);
}

int	replace_var(t_data *data, t_token *token, char *var_name, int *index)
{
	char	*varname_tmp;
	char	*before_var;
	char	*after_var;
	char	*final_join;
	char	*path_join;

	varname_tmp = ft_strjoin("$", var_name);
	before_var = ft_substr(token->str, 0, (*index - 1));
	if (!before_var)
		before_var = NULL;
	if (ft_strlen(token->str) == *index + ft_strlen(varname_tmp) - 1)
		after_var = NULL;
	else
		after_var = ft_substr(token->str, *index + \
			ft_strlen(varname_tmp) - 1, ft_strlen(token->str));
	path_join = NULL;
	if (!before_var && !after_var && get_env_value(data, var_name) == NULL)
		final_join = ft_calloc(sizeof(char), 1);
	else if (!before_var && !after_var)
		final_join = ft_strdup(get_env_value(data, var_name));
	else if (get_env_value(data, var_name) == NULL)
		final_join = var_not_found(before_var, after_var, index);
	else
	{
		path_join = ft_strjoin(before_var, get_env_value(data, var_name));
		*index = ft_strlen(path_join);
		if (after_var)
			final_join = ft_strjoin(path_join, after_var);
		else
			final_join = ft_strdup(path_join);
	}
	free(token->str);
	token->str = final_join;
	// if (ft_strlen(token->str) == 0)
	// 	remove_empty_token(data->token, token);
	free_allocs(varname_tmp, before_var, after_var, path_join);
	return (*index);
}
