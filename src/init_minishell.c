/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:05:43 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/30 20:24:07 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	print_cmd(data->cmd_lst);
	// if (start_execution(data))
	// 	return (1);
	return (0);
}

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
			break ;
		}
	}
	return (path);
}

// init env path
int	init_env_path(t_data **data, char **envp)
{
	int		i;
	char	*my_path;

	i = -1;
	my_path = NULL;
	if (arr_length(envp) == 0)
		return (ft_error("Error: loading the ENV problem!"), 1);
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
	free(my_path);
	return (0);
}

// initialize my data struct
int	init_data(t_data **data, char **envp)
{
	(*data)->input = NULL;
	(*data)->cmd_lst = NULL;
	(*data)->token = NULL;
	(*data)->envi = NULL;
	(*data)->path = NULL;
	if (init_env_path(data, envp))
		return (1);
	return (0);
}
