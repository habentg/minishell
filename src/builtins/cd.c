/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:17:17 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/29 19:59:49 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	@ updating PWD && OLDPWD after cd
*/
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
			if (tmp->value)
				free(tmp->value);
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

/*
	% since we are using our linked list to add/delete/update our env values,
		we need to convert it to an array every time we update it.
*/
void	update_envi(t_data *data)
{
	char	**tmp_arr;
	char	*tmp_path;

	tmp_arr = NULL;
	env_lst_to_arr(data);
	tmp_path = get_path(data->envi, "PATH");
	if (!tmp_path || !ft_strlen(tmp_path) \
		|| !ft_strncmp_custom(tmp_path, "", 1))
	{
		if (data->path)
			ft_clean_arr(data->path);
		data->path = (char **)malloc(sizeof(char *) * 1);
		data->path[0] = NULL;
	}
	else
	{
		ft_clean_arr(data->path);
		tmp_arr = ft_split(tmp_path, ':');
		data->path = tmp_arr;
	}
	if (tmp_path)
		free(tmp_path);
}

/*
	this fuc is used to handle the a/b/c/.. case
	# every time we change dir, we check if we can access the cwd.
		* if we cant we use the one we saved in the data struct to avoid segfault
	we need to update the env_lst for PWD & OLDPWD as well
*/
int	change_dir_updata_envi(t_data *data, char *path)
{
	char	*ret;
	char	cwd[PATH_MAX];
	char	*tmp_ret;

	ret = NULL;
	tmp_ret = NULL;
	if (chdir(path) != 0)
		return (display_error_2("cd", path, NO_FILE_DIR), 1);
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		display_error_2("cd", "error retrieving current directory", \
			"getcwd: cannot access parent directories");
		tmp_ret = ft_strjoin(data->cwd, "/");
		ret = ft_strjoin(tmp_ret, path);
		free(tmp_ret);
	}
	else
		ret = (cwd);
	edit_env_lst(data, ret);
	update_envi(data);
	return (0);
}

/*
	$ if only cd is given or cd ~, find 'HOME' in the path and chdir to there.
	$ there shouldnt be more than two arguments for cd
	$ if cd - is given, find 'OLDPWD' in the path and chdir to there.
	$ if cd is given with a path, chdir to that path.
*/
int	handle_cd(t_cmd *cmd_node, t_data *data)
{
	char	*path;

	if (!cmd_node->cmdarg[1] || !ft_strncmp_custom(cmd_node->cmdarg[1], "~", 1))
	{
		path = get_env_value(data, "HOME");
		if (path == NULL)
			return (display_error("cd", "HOME not set"), 1);
		return (change_dir_updata_envi(data, path));
	}
	else
		path = cmd_node->cmdarg[1];
	if (ft_strncmp_custom(path, "-", 2) == 0)
	{
		path = get_env_value(data, "OLDPWD");
		if (path == NULL)
			return (display_error("cd", "OLDPWD not set"), 1);
		return (change_dir_updata_envi(data, path));
	}
	return (change_dir_updata_envi(data, path));
}
