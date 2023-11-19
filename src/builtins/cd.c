/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:17:17 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/19 10:01:16 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	edit_env_lst(t_data *data, char *abs_path)
{
	t_env	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (ft_strncmp_custom(tmp->key, "PWD", 3) != 0)
			update_oldpwd(data->env_lst, "");
		else if (ft_strncmp_custom(tmp->key, "PWD", 3) == 0)
		{
			update_oldpwd(data->env_lst, tmp->value);
			tmp->value = ft_strdup(abs_path);
			break ;
		}
		tmp = tmp->next;
	}
	free(data->cwd);
	if (get_env_value(data, "PWD"))
		data->cwd = ft_strdup(get_env_value(data, "PWD"));
	else
	{
		data->cwd = ft_strdup(abs_path);
		update_oldpwd(data->env_lst, "");
	}
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
		return (display_error_2("cd", path, NO_FILE_DIR), 1);
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		display_error_2("cd", "error retrieving current directory", \
			"getcwd: cannot access parent directories");
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

	if (!cmd_node->cmdarg[1] || ft_strncmp_custom(cmd_node->cmdarg[1], "~", 1) \
		== 0 || (cmd_node->cmdarg[1] && ft_strlen(cmd_node->cmdarg[1]) == 0))
	{
		path = get_path(data->envi, "HOME");
		if (path == NULL)
			return (display_error_2("cd", path, "HOME not set"), 1);
		return (change_dir_updata_envi(data, path));
	}
	else
		path = cmd_node->cmdarg[1];
	if (arr_length(cmd_node->cmdarg) > 2)
		return (display_error("cd", "to many arguments"), 0);
	if (ft_strncmp_custom(path, "-", 2) == 0)
	{
		path = get_path(data->envi, "OLDPWD");
		if (path == NULL)
			return (display_error_2("cd", path, "OLDPWD not set"), 1);
		return (change_dir_updata_envi(data, path));
	}
	return (change_dir_updata_envi(data, path));
}
