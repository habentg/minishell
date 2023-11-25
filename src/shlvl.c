/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:25:31 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/25 12:51:57 by hatesfam         ###   ########.fr       */
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
bool	shlvl_present(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 5))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_env	*shlvl_ptr(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 5))
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
	tmp = shlvl_ptr(data->env_lst);
	if (!tmp)
		return ;
	if (inc_dec == 1)
		upd_shlvl_value = ft_itoa(ft_atoi(shlvl_value) + 1);
	else if (inc_dec == 0)
	{
		ft_putendl_fd("exit", 1);
		upd_shlvl_value = ft_itoa(ft_atoi(shlvl_value) - 1);
	}
	if (upd_shlvl_value)
	{
		free(tmp->value);
		tmp->value = ft_strdup(upd_shlvl_value);
		update_envi(data);
		free(upd_shlvl_value);
	}
}

void	shlvl_increment(t_data *data, int inc_dec)
{
	if (shlvl_present(data->env_lst))
		update_shlvl(data, inc_dec);
	else
	{
		add_env_back(data, (char *[]){"SHLVL", "1", NULL});
		update_envi(data);
	}
}
