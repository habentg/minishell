/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:13:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 18:43:10 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		printf("declare -x %s", tmp->key);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

void	handle_export(t_data *data, t_cmd *cmd_node)
{
	char	**arr;

	arr = NULL;
	if (cmd_node->cmdarg[1] == NULL)
		print_export(data->env_lst);
	else
	{
		arr = ft_split(cmd_node->cmdarg[1], '=');
		if (!arr)
			return ;
		add_env_back(data, arr);
		ft_clean_arr(arr);
		update_envi(data);
	}
}
