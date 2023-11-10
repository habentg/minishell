/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:50:12 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/10 09:28:11 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*last_env_node(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = NULL;
	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return (NULL);
	new_node->key = NULL;
	new_node->value = NULL;
	if (key)
		new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

static void	replace_value(t_env **current_node, t_env *new_node)
{
	if ((*current_node)->value)
		free((*current_node)->value);
	if (new_node->value)
		(*current_node)->value = ft_strdup(new_node->value);
}

void	add_env_back(t_data *data, char **env_node_arr)
{
	t_env	*env_node;
	t_env	*tmp;

	if (!env_node_arr)
		return ;
	env_node = new_env_node(env_node_arr[0], env_node_arr[1]);
	tmp = data->env_lst;
	if (!data->env_lst)
		data->env_lst = env_node;
	else
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->key, env_node->key, \
				ft_strlen(env_node->key)) == 0)
			{
				replace_value(&tmp, env_node);
				return ;
			}
			tmp = tmp->next;
		}
		(last_env_node(data->env_lst))->next = env_node;
	}
}

int	ft_env_lsize(t_env *lst)
{
	int		i;
	t_env	*temp_node;

	temp_node = lst;
	i = 0;
	while (temp_node != NULL)
	{
		temp_node = temp_node->next;
		i++;
	}
	return (i);
}
