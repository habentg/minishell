/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:13:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/08 17:53:24 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	bubble_sort_utils(char **sorted_envi, char **envi, int length)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	i = -1;
	j = -1;
	while (++i < length)
		sorted_envi[i] = ft_strdup(envi[i]);
	i = -1;
	while (++i < length - 1)
	{
		j = -1;
		while (++j < length - i - 1)
		{
			if (ft_strncmp(sorted_envi[j], sorted_envi[j + 1], \
				ft_strlen(sorted_envi[j + 1])) > 0)
			{
				tmp = sorted_envi[j];
				sorted_envi[j] = sorted_envi[j + 1];
				sorted_envi[j + 1] = tmp;
			}
		}
	}
}

char	**sorted_envi(char **envi)
{
	int		length;
	char	**sorted_envi;

	length = arr_length(envi);
	sorted_envi = (char **)ft_calloc(sizeof(char *), (length + 1));
	if (!sorted_envi)
		return (NULL);
	bubble_sort_utils(sorted_envi, envi, length);
	return (sorted_envi);
}

void	print_export(char **envi_arr)
{
	char	**tmp_arr;
	int		i;

	i = -1;
	tmp_arr = sorted_envi(envi_arr);
	while (++i < arr_length(tmp_arr))
		printf("declare -x %s\n", tmp_arr[i]);
	if (tmp_arr)
		ft_clean_arr(tmp_arr);
}

void	handle_export(t_data *data, t_cmd *cmd_node)
{
	char	**arr;

	arr = NULL;
	if (cmd_node->cmdarg[1] == NULL)
		print_export(data->envi);
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
