/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:17:17 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/09 19:00:10 by hatesfam         ###   ########.fr       */
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
}

void	update_envi(t_data *data)
{
	char	**tmp_arr;
	char	*tmp_path;

	tmp_arr = NULL;
	env_lst_to_arr(data);
	tmp_path = get_path(data->envi, "PATH");
	if (tmp_path == NULL)
	{
		data->path = (char **)malloc(sizeof(char *) * 1);
		data->path[0] = NULL;
	}
	else
	{
		free(tmp_path);
		ft_clean_arr(data->path);
		tmp_arr = ft_split(get_path(data->envi, "PATH"), ':');
		data->path = tmp_arr;
	}
}

/*if only cd is given, find 'HOME' in the path and chdir to there*/
/*else, change to the path given give after 'cd', idk what comes after that*/
int	handle_cd(t_cmd *cmd_node, t_data *data)
{
	char	*path;
	char	full_path[PATH_MAX];

	if (cmd_node->cmdarg[1] == NULL || \
		ft_strncmp_custom(cmd_node->cmdarg[1], "~", 1) == 0)
	{
		path = get_path(data->envi, "HOME");
		if (path == NULL)
			return (ft_error("Error: HOME not set", 127), 1);
	}
	else
		path = cmd_node->cmdarg[1];
	if (getcwd(full_path, sizeof(full_path)) == NULL)
		return (ft_error("cd: getcwd: error retrieving current directory"\
			, 127), 0);
	if (chdir(path) == -1)
		return (display_error_2(path, NO_FILE_DIR, 1), 1);
	edit_env_lst(data, full_path);
	update_envi(data);
	return (0);
}
