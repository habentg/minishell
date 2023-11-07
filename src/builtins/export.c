/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:13:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/08 02:40:59 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	compare_first_char(const char *str1, const char *str2)
{
	return (str1[0] - str2[0]);
}

static void	bubble_sort_utils(char **sorted_envi, char **envi)
{
	int		length;
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	i = -1;
	j = -1;
	length = arr_length(envi);
	while (++i < length)
		sorted_envi[i] = ft_strdup(envi[i]);
	i = -1;
	while (++i < length - 1)
	{
		j = -1;
		while (++j < length - i - 1)
		{
			if (compare_first_char(sorted_envi[j], sorted_envi[j + 1]) > 0)
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
	sorted_envi = (char **)malloc(sizeof(char *) * (length + 1));
	if (!sorted_envi)
		return (NULL);
	bubble_sort_utils(sorted_envi, envi);
	return (sorted_envi);
}

void	print_export(char **envi_arr)
{
	char	**tmp_arr;
	int		i;

	i = -1;
	tmp_arr = sorted_envi(envi_arr);
	while (tmp_arr[++i])
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
