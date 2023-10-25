/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 22:40:02 by hatesfam         ###   ########.fr       */
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
	// if (start_execution(data))
	// 	return (1);
	return (0);
}

void	print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("arr[%d]: %s\n", i, arr[i]);
}

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

// initialize my data struct
int	init_data(t_data **data, char *input, char **envp)
{
	int		i;
	char	*my_path;

	i = -1;
	my_path = NULL;
	(*data)->input = input;
	(*data)->cmd = NULL;
	(*data)->token = NULL;
	// (*data)->envi = (char **)malloc((sizeof(char *)),
	// 	(arr_length(envp)));
	(*data)->envi = malloc((sizeof(char *)) * (arr_length(envp)));
	if (!(*data)->envi)
		return (1);
	while (envp[++i])
		(*data)->envi[i] = ft_strdup(envp[i]);
	my_path = get_path((*data)->envi, "PATH");
	(*data)->path = ft_split(my_path, ':');
	// print_arr((*data)->path);
	free(my_path);
	return (0);
}

// launch minishell
int	launch_minishell(t_data *data, char **envp)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (ft_strncmp_custom(input, "exit", 4) == 0)
		{
			printf("exit\n");
			return (0);
		}
		if (init_data(&data, input, envp))
			return (1);
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
		if (init_program(data))
			return (1);
		ft_clean_data(&data);
		// free(input);
	}
	return (0);
}

// program entry
/*Allocating our general data struct and launching our minishell*/
int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)av;
	if (ac != 1)
		return (1);
	// data = NULL;
	data = (t_data *)malloc(sizeof(t_data));
	// if (!data)
	// 	return (1);
	if (launch_minishell(data, envp))
		return (1);
	ft_clean_data_exit(&data);
	return (0);
}
