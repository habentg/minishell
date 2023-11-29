/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:53:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/29 16:51:56 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_data *data, char *var_name)
{
	t_env	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, var_name, ft_strlen(var_name)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_heredoc_expandable(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '$')
				return (0);
			else if (str[i + 1])
				return (1);
		}
		i++;
	}
	return (0);
}

char	*get_var_name(char *content, int *i)
{
	int	k;

	k = *i;
	while (content[*i] && (content[*i] != '$' && content[*i] != ' ' \
		&& !is_qoute(content[*i]) && !is_operator(content[*i])))
		(*i)++;
	return (ft_substr(content, k, *i - k));
}

int	for_real_expand(t_data *data, char *content, int *i, int tmp_fd)
{
	char	*var_name;
	char	*exp_var;

	(*i)++;
	var_name = get_var_name(content, i);
	exp_var = get_env_value(data, var_name);
	if (!exp_var)
		exp_var = NULL;
	ft_putstr_fd(exp_var, tmp_fd);
	free(var_name);
	return (*i--);
}
