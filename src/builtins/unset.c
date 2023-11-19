/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 07:18:57 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/19 16:24:50 by hatesfam         ###   ########.fr       */
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
	t_env	*next_env;

	curr_env = *env_lst;
	prev_env = NULL;
	next_env = NULL;
	while (curr_env)
	{
		if (ft_strncmp_custom(curr_env->key, key_re, ft_strlen(key_re)) == 0)
		{
			next_env = curr_env->next;
			if (curr_env == *env_lst)
				*env_lst = next_env;
			else
				prev_env->next = next_env;
			free_env_node(curr_env);
			break ;
		}
		else
		{
			prev_env = curr_env;
			curr_env = curr_env->next;
		}
	}
}

/*deletes an env variable that matches the key, has to be valid key
	% the u_flag is just to check if there was an invalid key
	$ so i can apdate the envi array from the env_list
*/
int	handle_unset(t_data *data, t_cmd *cmd_node)
{
	int	i;

	i = 1;
	while (cmd_node->cmdarg[i])
	{
		if (!valid_key_check(cmd_node->cmdarg[i], 1))
			display_error_2("unset", cmd_node->cmdarg[i], \
				"not a valid identifier");
		else
			remove_env_node(&data->env_lst, cmd_node->cmdarg[i]);
		i++;
	}
	update_envi(data);
	return (0);
}
