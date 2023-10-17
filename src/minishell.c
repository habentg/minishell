/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 16:38:26 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// init minishell
int	start_program(t_data *data, char *input, char **envp)
{
	if (possible_error(input))
		return (1);
	if (start_lexing(data, input, envp))
		return (1);
	if (start_expansion(data, envp))
		return (1);
	return (0);
}

// initialize my data
int	init_data(t_data **data, char *input, char **envp)
{
	int	i;

	i = -1;
	(*data)->input = input;
	(*data)->cmds = NULL;
	(*data)->token = NULL;
	(*data)->envi = (char **)malloc((sizeof(char *) * 1) * arr_length(envp));
	if (!(*data)->envi)
		return (1);
	while (envp[++i])
		(*data)->envi[i] = ft_strdup(envp[i]);
	// (*data)->envi[i] = NULL;
	return (0);
}

// program entry
int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)av;
	input = NULL;
	if (ac != 1)
		return (1);
	printf("ENV: %s\n", envp[0]);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(data);
			free(input);
			return (ft_error("exit", 0), 1);
		}
		if (init_data(&data, input, envp))
			return (ft_clean_data(&data), 1);
		if (start_program(data, input, envp))
			return (ft_clean_data(&data), 1);
		if (ft_strlen(input) > 0)
			add_history(input);
	}
	return (0);
}
