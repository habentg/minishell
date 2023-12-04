/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:50:12 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/01 22:16:57 by hatesfam         ###   ########.fr       */
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

t_env	*env_node_template(void)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->key = NULL;
	env_node->value = NULL;
	env_node->next = NULL;
	return (env_node);
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = env_node_template();
	if (!new_node)
		return (NULL);
	if (key)
		new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	return (new_node);
}

void	add_env_back(t_data *data, char **env_node_arr)
{
	t_env	*env_node;

	if (!env_node_arr)
		return ;
	env_node = new_env_node(env_node_arr[0], env_node_arr[1]);
	if (!env_node)
		return ;
	if (!data->env_lst)
		data->env_lst = env_node;
	else
	{
		(last_env_node(data->env_lst))->next = env_node;
	}
}
