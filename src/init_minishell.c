/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:05:43 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/05 22:59:52 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// get path from envi
char	*get_path(char **envp, char *key)
{
	int		i;
	char	*path;

	i = -1;
	path = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
		{
			path = ft_strdup(envp[i] + ft_strlen(key) + 1);
			if (!path)
				return (NULL);
			break ;
		}
	}
	return (path);
}

// env_lst to arr
int	create_env_lst(t_data **data)
{
	int		i;
	char	**tmp_arr;

	i = -1;
	tmp_arr = NULL;
	while ((*data)->envi[++i])
	{
		if (strncmp((*data)->envi[i], "LS_COLORS", 9) == 0)
		{
			tmp_arr = (char **)malloc(sizeof(char *) * 3);
			tmp_arr[0] = ft_strdup("LS_COLORS");
			tmp_arr[1] = ft_strdup((*data)->envi[i] + 11);
			tmp_arr[2] = NULL;
		}
		else
			tmp_arr = ft_split((*data)->envi[i], '=');
		add_env_back(*data, tmp_arr);
		ft_clean_arr(tmp_arr);
		tmp_arr = NULL;
	}
	return (0);
}

// init env path
int	init_env_path(t_data **data, char **envp)
{
	int		i;
	char	*my_path;

	i = -1;
	my_path = NULL;
	if (arr_length(envp) == 0)
		return (ft_error("Error: problem in retreiving the ENV!"), 1);
	(*data)->envi = (char **)ft_calloc((sizeof(char *)), \
		(arr_length(envp) + 1));
	if (!(*data)->envi)
		return (1);
	while (++i < arr_length(envp) && envp[i])
		(*data)->envi[i] = ft_strdup(envp[i]);
	(*data)->envi[i] = NULL;
	my_path = get_path((*data)->envi, "PATH");
	if (!my_path)
		return (ft_error("Error: couldnt get the path!"), 1);
	(*data)->path = ft_split(my_path, ':');
	if (!(*data)->path)
		return (ft_error("Error: couldnt split the path!"), 1);
	free(my_path);
	return (0);
}

// init minishell program
int	init_program(t_data *data)
{
	if (possible_error(&data))
		return (0);
	if (start_lexing(data))
		return (1);
	if (operator_pipe_error(data))
		return (0);
	if (start_expansion(data))
		return (1);
	if (start_cmd_extraction(data))
		return (1);
	if (start_execution(data))
		return (1);
	return (0);
}
