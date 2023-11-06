/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 07:18:57 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 16:45:05 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_node(t_env *env_node)
{
	if (env_node->key)
		free(env_node->key);
	if (env_node->value)
		free(env_node->value);
	free(env_node);
}

void	remove_env_node(t_env **env_lst, char *key_re)
{
	t_env	*curr_env;
	t_env	*prev_env;

	curr_env = *env_lst;
	while (curr_env)
	{
		if (ft_strncmp(curr_env->key, key_re, ft_strlen(key_re)) == 0)
		{
			if (curr_env == *env_lst)
			{
				if ((*env_lst)->next)
					*env_lst = (*env_lst)->next;
				else
					*env_lst = NULL;
			}
			else
				prev_env->next = curr_env->next;
			free_env_node(curr_env);
		}
		prev_env = curr_env;
		curr_env = curr_env->next;
	}
}

void	handle_unset(t_data *data, t_cmd *cmd_node)
{
	int	i;

	i = 1;
	while (cmd_node->cmdarg[i])
	{
		remove_env_node(&data->env_lst, cmd_node->cmdarg[i]);
		i++;
	}
	update_envi(data);
}