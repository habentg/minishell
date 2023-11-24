/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:53:39 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/24 15:08:23 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	dont forget to free the allocated memory
*/
void	free_allocs(char *before_var, char *after_var)
{
	free(before_var);
	free(after_var);
}

/*
	var not found!
		join the before_var and after_var together.
		done!
*/
char	*var_not_found(t_token **token, char *b_var, char *a_var)
{
	char	*final_join;

	final_join = NULL;
	if (!b_var && !a_var)
	{
		final_join = (char *)ft_calloc(sizeof(char), 1);
		(*token)->was_mpty_before = 0;
	}
	else if (!b_var)
		final_join = ft_strdup(a_var);
	else if (!a_var)
		final_join = ft_strdup(b_var);
	else
		final_join = ft_strjoin(b_var, a_var);
	return (final_join);
}

char	*var_found(t_data *data, char *b_var, char *a_var, char *var_name)
{
	char	*final_join;
	char	*path_join;

	path_join = NULL;
	final_join = NULL;
	if (!b_var && !a_var)
		final_join = ft_strdup(get_env_value(data, var_name));
	else if (!b_var)
		final_join = ft_strjoin(get_env_value(data, var_name), a_var);
	else if (!a_var)
		final_join = ft_strjoin(b_var, get_env_value(data, var_name));
	else
	{
		path_join = ft_strjoin(b_var, get_env_value(data, var_name));
		final_join = ft_strjoin(path_join, a_var);
	}
	free(path_join);
	return (final_join);
}

/*
	VAR FINDER and REPLACER
		>> we have var_name
		>> we save everything before & After var_name
		>> find the varname in the env_lst
		>> if found, replace it with the value
		>> if not found, replace it with empty string("")
		>> join everything back together
		pretty much it
*/
int	replace_var(t_data *data, t_token **token, char *var_name, int *index)
{
	char	*before_var;
	char	*after_var;
	char	*final_join;

	before_var = ft_substr((*token)->str, 0, (*index - 1));
	final_join = NULL;
	if (!before_var)
		before_var = NULL;
	if (ft_strlen((*token)->str) == *index + ft_strlen(var_name))
		after_var = NULL;
	else
		after_var = ft_substr((*token)->str, *index + \
			ft_strlen(var_name), ft_strlen((*token)->str));
	if (get_env_value(data, var_name) == NULL)
		final_join = var_not_found((token), before_var, after_var);
	else
		final_join = var_found(data, before_var, after_var, var_name);
	free((*token)->str);
	(*token)->str = final_join;
	free_allocs(before_var, after_var);
	return (0);
}
