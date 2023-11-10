/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/10 10:37:39 by hatesfam         ###   ########.fr       */
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
	(void) envp;
	if (create_env_lst(data))
		return (1);
	return (0);
}

// launch minishell
int	launch_minishell(t_data *data)
{
	char	*input_res;

	input_res = NULL;
	while (1)
	{
		printf("\033[1;34m[%d]\033[0m", g_exit_status);
		input_res = readline(PROMPT);
		if (!input_res)
		{
			printf("exit\n");
			ft_clean_data_done(&data, 0);
			exit(0);
		}
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

// increment shlvl
void	shlvl_increment(t_data *data)
{
	char	*curr_shlvl;
	char	**arr;

	arr = NULL;
	curr_shlvl = get_path(data->envi, "SHLVL");
	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("SHLVL");
	if (!curr_shlvl)
		arr[1] = ft_strdup("1");
	else
		arr[1] = ft_itoa(ft_atoi(curr_shlvl) + 1);
	arr[2] = NULL;
	add_env_back(data, arr);
	update_envi(data);
	ft_clean_arr(arr);
	free(curr_shlvl);
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
	if (init_data(&data, envp))
		return (ft_clean_data_done(&data, 0), 1);
	shlvl_increment(data);
	if (launch_minishell(data))
		return (ft_clean_data_done(&data, 0), 1);
	ft_clean_data_done(&data, 0);
	return (0);
}
