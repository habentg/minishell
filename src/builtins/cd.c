/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:17:17 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 16:54:59 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	edit_env_lst(t_data *data, char *abs_path)
{
	t_env	*tmp;
	char	**oldpwd_arr;

	tmp = data->env_lst;
	while (tmp)
	{
		if (ft_strncmp_custom(tmp->key, "PWD", 4) == 0)
		{
			oldpwd_arr = (char **)malloc(sizeof(char *) * 3);
			oldpwd_arr[0] = ft_strdup("OLDPWD");
			oldpwd_arr[1] = ft_strdup(tmp->value);
			oldpwd_arr[2] = NULL;
			add_env_back(data, oldpwd_arr);
			free(tmp->value);
			ft_clean_arr(oldpwd_arr);
			tmp->value = ft_strdup(abs_path);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_envi(t_data *data)
{
	env_lst_to_arr(data);
}

/*if only cd is given, find 'HOME' in the path and chdir to there*/
/*else, change to the path given give after 'cd', idk what comes after that*/
void	handle_cd(t_cmd *cmd_node, t_data *data)
{
	char	*path;
	char	full_path[PATH_MAX];

	if (cmd_node->cmdarg[1] == NULL || \
		ft_strncmp_custom(cmd_node->cmdarg[1], "~", 1) == 0)
	{
		path = get_path(data->envi, "HOME");
		if (path == NULL)
		{
			ft_error("Error: HOME not set");
			return ;
		}
	}
	else
		path = cmd_node->cmdarg[1];
	if (chdir(path) == -1 || getcwd(full_path, sizeof(full_path)) == NULL)
	{
		file_dir_not_found(path);
		return ;
	}
	edit_env_lst(data, full_path);
	update_envi(data);
}
