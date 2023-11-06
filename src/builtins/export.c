/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:13:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 07:14:18 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export_add(t_data *data, t_cmd *cmd_node)
{
	(void)data;
	(void)cmd_node;
	printf("handle_export_add: [%s]\n", cmd_node->cmdarg[1]);
}

void	print_export(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		printf("declare -x %s", tmp->key);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		tmp = tmp->next;
	}
}

int	handle_export(t_data *data, t_cmd *cmd_node)
{
	char	**arr;

	arr = NULL;
	if (cmd_node->cmdarg[1] == NULL)
		return (print_export(data->env_lst), 0);
	else
	{
		arr = ft_split(cmd_node->cmdarg[1], '=');
		if (!arr)
			return (1);
		print_arr(arr);
		add_env_back(data, arr);
		ft_clean_arr(arr);
		update_envi(data);
	}
	return (0);
}
