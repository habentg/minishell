/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:17:17 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/16 11:41:13 by hatesfam         ###   ########.fr       */
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
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
		{
			oldpwd_arr = (char **)malloc(sizeof(char *) * 3);
			oldpwd_arr[0] = ft_strdup("OLDPWD");
			oldpwd_arr[1] = ft_strdup(tmp->value);
			oldpwd_arr[2] = NULL;
			add_env_back(data, oldpwd_arr);
			if (tmp->value)
				free(tmp->value);
			ft_clean_arr(oldpwd_arr);
			tmp->value = ft_strdup(abs_path);
			break ;
		}
		tmp = tmp->next;
	}
	free(data->cwd);
	data->cwd = ft_strdup(get_env_value(data, "PWD"));
}

void	update_envi(t_data *data)
{
	char	**tmp_arr;
	char	*tmp_path;
	char	*path_to_split;

	tmp_arr = NULL;
	path_to_split = NULL;
	env_lst_to_arr(data);
	tmp_path = get_path(data->envi, "PATH");
	if (tmp_path == NULL)
	{
		data->path = (char **)malloc(sizeof(char *) * 1);
		data->path[0] = NULL;
	}
	else
	{
		ft_clean_arr(data->path);
		free(tmp_path);
		path_to_split = get_path(data->envi, "PATH");
		tmp_arr = ft_split(path_to_split, ':');
		free(path_to_split);
		data->path = tmp_arr;
	}
}

int	change_dir_updata_envi(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	tmp = NULL;
	if (chdir(path) != 0)
		return (display_error_2("cd", path, NO_FILE_DIR, 1), 1);
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		display_error_2("cd", "error retrieving current directory", \
			"getcwd: cannot access parent directories", 1);
		ret = ft_strjoin(data->cwd, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free(tmp);
	}
	else
		ret = ft_strdup(cwd);
	edit_env_lst(data, ret);
	update_envi(data);
	return (0);
}

/*if only cd is given, find 'HOME' in the path and chdir to there*/
/*else, change to the path given give after 'cd', idk what comes after that*/
int	handle_cd(t_cmd *cmd_node, t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	if (!cmd_node->cmdarg[1] || ft_strncmp_custom(cmd_node->cmdarg[1], "~", 1) \
		== 0 || (cmd_node->cmdarg[1] && ft_strlen(cmd_node->cmdarg[1]) == 0))
	{
		path = get_path(data->envi, "HOME");
		if (path == NULL)
			return (display_error_2("cd", path, "HOME not set", 1), 1);
		return (change_dir_updata_envi(data, path));
	}
	else
		path = cmd_node->cmdarg[1];
	if (arr_length(cmd_node->cmdarg) > 2)
		return (display_error("cd", "to many arguments", 1), 0);
	if (ft_strncmp_custom(path, "-", 2) == 0)
	{
		path = get_path(data->envi, "OLDPWD");
		if (path == NULL)
			return (display_error_2("cd", path, "OLDPWD not set", 1), 1);
		return (change_dir_updata_envi(data, path));
	}
	return (change_dir_updata_envi(data, path));
}
