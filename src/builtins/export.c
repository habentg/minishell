/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:13:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/01 22:23:27 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_lst_to_arr(t_data *data)
{
	t_env	*tmp;
	char	**tmp_arr;
	char	*tmp_str;
	int		i;

	i = 0;
	tmp = data->env_lst;
	tmp_str = NULL;
	tmp_arr = (char **)malloc(sizeof(char *) * (ft_env_lsize(tmp) + 1));
	while (tmp)
	{
		if (tmp->value == NULL)
			tmp_arr[i] = ft_strdup(tmp->key);
		else
		{
			tmp_str = ft_strjoin(tmp->key, "=");
			tmp_arr[i] = ft_strjoin(tmp_str, tmp->value);
			free(tmp_str);
		}
		tmp = tmp->next;
		i++;
	}
	tmp_arr[i] = NULL;
	ft_clean_arr(data->envi);
	data->envi = tmp_arr;
}

int	print_export(t_data *data, char **envi_arr)
{
	char	**tmp_arr;
	char	**split_str;
	int		i;

	i = -1;
	split_str = NULL;
	tmp_arr = sorted_envi(envi_arr);
	if (!tmp_arr)
		return (ft_error(data, "sorting envi failed", 1), 1);
	while (tmp_arr[++i])
	{
		split_str = ft_split_custom(tmp_arr[i]);
		printf("declare -x %s", split_str[0]);
		if (split_str[1])
			printf("=\"%s\"", split_str[1]);
		printf("\n");
		ft_clean_arr(split_str);
	}
	if (tmp_arr)
		ft_clean_arr(tmp_arr);
	return (0);
}

void	add_or_replace_export(t_data *data, char **arr)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = env_node_ptr(data->env_lst, arr[0]);
	if (!tmp)
		add_env_back(data, arr);
	else
	{
		if (arr[1])
		{
			free(tmp->value);
			tmp->value = ft_strdup(arr[1]);
		}
	}
}

int	handle_export_util(t_data *data, t_cmd *cmd_node, int i, char **arr)
{
	int		ret;

	ret = 0;
	while (cmd_node->cmdarg[++i])
	{
		arr = ft_split_custom(cmd_node->cmdarg[i]);
		if (!arr)
			continue ;
		if (!valid_key_check(arr[0], 0))
		{
			ft_clean_arr(arr);
			display_error_2("export", cmd_node->cmdarg[i], NVI);
			ret = 1;
			continue ;
		}
		ret = 0;
		add_or_replace_export(data, arr);
		ft_clean_arr(arr);
	}
	return (ret);
}

// key should be alpha-numerical only -> otheriwse error
int	handle_export(t_data *data, t_cmd *cmd_node)
{
	int		i;
	char	**arr;

	arr = NULL;
	i = 0;
	if (cmd_node->cmdarg[1] == NULL)
		return (print_export(data, data->envi));
	if (handle_export_util(data, cmd_node, i, arr))
		return (1);
	update_envi(data);
	return (0);
}
