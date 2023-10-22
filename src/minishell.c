/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/22 19:45:06 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// init minishell program
int	init_program(t_data *data)
{
	if (possible_error(&data))
		return (1);
	if (start_lexing(data))
		return (1);
	if (operator_pipe_error(data))
		return (1);
	if (start_expansion(data))
		return (1);
	if (start_cmd_extraction(data))
		return (1);
	return (0);
}

// initialize my data struct
int	init_data(t_data **data, char *input, char **envp)
{
	int	i;

	i = -1;
	(*data)->input = input;
	(*data)->cmds = NULL;
	(*data)->token = NULL;
	(*data)->envi = (char **)malloc((sizeof(char *)) * (arr_length(envp) + 1));
	if (!(*data)->envi)
		return (1);
	while (envp[++i])
		(*data)->envi[i] = ft_strdup(envp[i]);
	(*data)->envi[arr_length(envp)] = NULL;
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
		if (ft_strncmp(input, "exit", 4) == 0)
			return (ft_error("exit"), 1);
		if (init_data(&data, input, envp))
			return (1);
		if (init_program(data))
			return (1);
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
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
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (launch_minishell(data, envp))
		return (1);
	ft_clean_data(&data);
	return (0);
}
