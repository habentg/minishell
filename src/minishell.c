/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/29 16:43:24 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// launch minishell
int	launch_minishell(t_data *data, char **envp)
{
	char	*input;

	input = NULL;
	if (init_data(&data, envp))
		return (1);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (ft_strlen(input) == 0)
			continue ;
		if (ft_strncmp_custom(input, "exit", 4) == 0)
		{
			printf("exit\n");
			return (0);
		}
		data->input = input;
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
		return (ft_clean_data_exit(&data), 1);
	ft_clean_data_exit(&data);
	return (0);
}
