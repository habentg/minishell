/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:13:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/13 05:45:52 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_lst_to_arr(t_data *data)
{
	t_env	*tmp;
	char	**tmp_arr;
	int		i;

	i = 0;
	tmp = data->env_lst;
	tmp_arr = (char **)malloc(sizeof(char *) * (ft_env_lsize(tmp) + 1));
	while (tmp)
	{
		if (tmp->value == NULL)
			tmp_arr[i] = ft_strdup(tmp->key);
		else
			tmp_arr[i] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
	tmp_arr[i] = NULL;
	ft_clean_arr(data->envi);
	data->envi = tmp_arr;
}

void	print_export(char **envi_arr)
{
	char	**tmp_arr;
	char	**split_str;
	int		i;

	i = -1;
	split_str = NULL;
	tmp_arr = sorted_envi(envi_arr);
	while (tmp_arr[++i])
	{
		split_str = ft_split_custom(tmp_arr[i]);
		printf("declare -x %s", split_str[0]);
		if (split_str[1])
			printf("\'%s\'\n", split_str[1]);
		ft_clean_arr(split_str);
	}
	if (tmp_arr)
		ft_clean_arr(tmp_arr);
}

static int	valid_key_check(char *key)
{
	int	i;

	i = -1;
	if (!key)
		return (0);
	while (key[++i])
	{
		if (ft_isalpha(key[i]) || key[i] == '=')
			continue ;
		return (0);
	}
	return (1);
}

// key should be alpha-numerical only -> otheriwse error
int	handle_export(t_data *data, t_cmd *cmd_node)
{
	int		i;
	char	**arr;

	arr = NULL;
	i = 0;
	if (cmd_node->cmdarg[1] == NULL)
		return (print_export(data->envi), 0);
	while (cmd_node->cmdarg[++i])
	{
		if (ft_strlen(cmd_node->cmdarg[i]) == 0 || (ft_strlen \
			(cmd_node->cmdarg[i]) == 1 && cmd_node->cmdarg[i][0] == '='))
		{
			display_error_2("export", " `'", "not a valid identifier", 1);
			continue ;
		}
		arr = ft_split_custom(cmd_node->cmdarg[i]);
		if (!valid_key_check(arr[0]))
			return (display_error_2("export", arr[0], \
				"not a valid identifier", 1), 1);
		add_env_back(data, arr);
		ft_clean_arr(arr);
	}
	update_envi(data);
	return (0);
}
