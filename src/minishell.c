/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/23 14:41:08 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// increment/decrement shlvl
/*
	&& get the current shlvl value
	&& create a new env node with the new shlvl value
	&& add it to the env_lst
	&& update the envi
*/
void	shlvl_increment(t_data *data, int inc_dec)
{
	char	*curr_shlvl;
	char	**arr;

	arr = NULL;
	curr_shlvl = get_path(data->envi, "SHLVL");
	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup("SHLVL");
	if (!curr_shlvl)
		arr[1] = ft_strdup("1");
	else if (inc_dec == 1)
		arr[1] = ft_itoa(ft_atoi(curr_shlvl) + 1);
	else if (inc_dec == 0)
	{
		ft_putendl_fd("exit", 1);
		arr[1] = ft_itoa(ft_atoi(curr_shlvl) - 1);
	}
	arr[2] = NULL;
	add_env_back(data, arr);
	update_envi(data);
	ft_clean_arr(arr);
	free(curr_shlvl);
}

// initialize my data struct
/*
	!! initialize all the data struct members
	!! get & save the current working directory (gonna need it in cd builtin)
	!! initialize the path variables
	!! create the env_lst from the envi -> easy to manipulate
	NOTE: I am getting the OLDPWD from envp, I am not adding it my self.
*/
int	init_data(t_data **data, char **envp)
{
	char	wd[PATH_MAX];

	(*data)->input = NULL;
	(*data)->cmd_lst = NULL;
	(*data)->token = NULL;
	(*data)->envi = NULL;
	(*data)->path = NULL;
	(*data)->env_lst = NULL;
	(*data)->exit_code = 0;
	(*data)->ch_pid = -1;
	(*data)->cwd = ft_strdup(getcwd(wd, PATH_MAX));
	if (!(*data)->cwd)
		return (ft_error(*data, "data init failure", 255), 1);
	if (init_env_path(data, envp))
		return (ft_error(*data, "path init failure", 255), 1);
	if (create_env_lst(data))
		return (ft_error(*data, "env_lst init failure", 255), 1);
	empty_oldpwd((*data)->env_lst);
	return (0);
}

// launch minishell
/*
	This is were the magic happens
	%% get the input from the user, if CTRL + D, clean & exit
	%% if the input is empty, continue (nothing to parse)
	%% save the input in the data struct
	%% add the input to the history
	%% initialize the program (lexer -> parser -> executor)
	%% clean the data struct (input, cmd_lst, token), ready for the next input
*/
int	launch_minishell(t_data *data)
{
	char	*input_res;

	input_res = NULL;
	while (1)
	{
		sig_handler();
		input_res = readline(PROMPT);
		if (g_exit_status == 130)
		{
			data->exit_code = g_exit_status;
			g_exit_status = 0;
		}
		if (!input_res)
			ft_clean_data_done(&data, 2);
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
/*
 => Allocating & initializing our general data struct 
 => incrementing the shell level (gonna be helpfull for exit builtin)
 => and launching our minishell
 => and cleaning up*/
int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)av;
	if (ac > 1)
		return (display_error(av[1], NO_FILE_DIR), 127);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(&data, envp))
		return (ft_clean_data_done(&data, 0), 1);
	shlvl_increment(data, 1);
	if (launch_minishell(data))
		return (ft_clean_data_done(&data, 0), 1);
	ft_clean_data_done(&data, 0);
}
