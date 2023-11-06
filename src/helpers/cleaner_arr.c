/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:16:16 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 01:50:42 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_arr(char **argv)
{
	int	i;

	i = 0;
	if (!argv || arr_length(argv) == 0)
		return ;
	while (i < arr_length(argv))
	{
		if (argv[i] != NULL)
			free(argv[i]);
		i++;
	}
	if (argv)
		free(argv);
}

int	arr_length(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	free_env_lst(t_data *data)
{
	t_env	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		if (tmp)
			free(tmp);
		tmp = tmp->next;
	}
}
