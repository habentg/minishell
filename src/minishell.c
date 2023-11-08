/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/08 05:19:24 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// initialize my data struct
int	init_data(t_data **data, char **envp)
{
	(*data)->input = NULL;
	(*data)->cmd_lst = NULL;
	(*data)->token = NULL;
	(*data)->envi = NULL;
	(*data)->path = NULL;
	(*data)->env_lst = NULL;
	if (init_env_path(data, envp))
		return (1);
	if (create_env_lst(data))
		return (1);
	return (0);
}

// launch minishell
int	launch_minishell(t_data *data, char **envp)
{
	char	*input_res;

	input_res = NULL;
	if (init_data(&data, envp))
		return (1);
	while (1)
	{
		printf("\033[1;34m[%d]\033[0m", g_exit_status);
		input_res = readline(PROMPT);
		if (!input_res)
			break ;
		if (ft_strlen(input_res) == 0)
			continue ;
		data->input = input_res;
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
		if (init_program(data))
			return (1);
		ft_clean_data(&data);
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
		return (ft_clean_data_done(&data), 1);
	ft_clean_data_done(&data);
	return (0);
}
