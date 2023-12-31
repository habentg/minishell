/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:25:31 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/04 23:29:22 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// increment/decrement shlvl
/*
	&& get the current shlvl value
	&& create a new env node with the new shlvl value
	&& add it to the env_lst
	&& update the envi
*/
t_env	*env_node_ptr(t_env *env_lst, char *key)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		if (!ft_strncmp_custom(tmp->key, key, ft_strlen(key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_shlvl(t_data *data, int inc_dec)
{
	char	*shlvl_value;
	char	*upd_shlvl_value;
	t_env	*tmp;

	upd_shlvl_value = NULL;
	shlvl_value = get_env_value(data, "SHLVL");
	if (!shlvl_value)
		shlvl_value = "1";
	tmp = env_node_ptr(data->env_lst, "SHLVL");
	if (inc_dec == 1)
		upd_shlvl_value = ft_itoa(ft_atoi(shlvl_value) + 1);
	else if (inc_dec == 0)
	{
		ft_putendl_fd("exit", 2);
		upd_shlvl_value = ft_itoa(ft_atoi(shlvl_value) - 1);
	}
	if (upd_shlvl_value)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = ft_strdup(upd_shlvl_value);
		update_envi(data);
		free(upd_shlvl_value);
	}
}

void	shlvl_increment(t_data *data, int inc_dec)
{
	if (env_node_ptr(data->env_lst, "SHLVL"))
		update_shlvl(data, inc_dec);
	else
	{
		add_env_back(data, (char *[]){"SHLVL", "1", NULL});
		update_envi(data);
	}
}
