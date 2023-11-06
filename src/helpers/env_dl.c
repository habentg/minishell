/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:50:12 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 07:11:41 by hatesfam         ###   ########.fr       */
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

	new_node = (t_env *)malloc(sizeof(t_env));
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

void	add_env_back(t_data *data, char **env_node_arr)
{
	t_env	*env_node;
	t_env	*tmp;

	if (!env_node_arr)
		return ;
	env_node = new_env_node(env_node_arr[0], env_node_arr[1]);
	tmp = data->env_lst;
	if (ft_strncmp_custom(env_node->key, "OLDPWD", 6) == 0)
	{
		while (tmp)
		{
			if (ft_strncmp_custom(tmp->key, "OLDPWD", 6) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(env_node->value);
				return ;
			}
			tmp = tmp->next;
		}
	}
	if (!data->env_lst)
		data->env_lst = env_node;
	else
		(last_env_node(data->env_lst))->next = env_node;
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

void	env_lst_to_arr(t_data *data)
{
	t_env	*tmp;
	char	*tmp_join;
	char	**tmp_arr;
	int		i;

	i = 0;
	tmp_join = NULL;
	tmp = data->env_lst;
	tmp_arr = (char **)malloc(sizeof(char *) * (ft_env_lsize(tmp) + 1));
	while (tmp)
	{
		if (tmp->value == NULL)
			tmp_arr[i] = ft_strdup(tmp->key);
		else
		{
			tmp_join = ft_strjoin(tmp->key, "=");
			tmp_arr[i] = ft_strjoin(tmp_join, tmp->value);
			free(tmp_join);
		}
		tmp = tmp->next;
		i++;
	}
	tmp_arr[i] = NULL;
	ft_clean_arr(data->envi);
	data->envi = tmp_arr;
}
