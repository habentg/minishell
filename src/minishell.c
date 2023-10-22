/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/22 13:20:36 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// init minishell program
/*
after we successfully initialize our general data, we will:
	1, start with basic error handling such as:
		>> opened but unclosed quotes
		>> pipe at the end
		>> redirections at the end
	2, we start lexical analysis - where we tokenize each element of the input
		* once again, if not successfull we clean allocated memory, throw meaningful error message and exit smoothly,
	3. after we have a double linked list of tokenized elements, we check for some more error checking for these conditions:
		* > | respectively is an error.
		* < | respectively is an error.
		* << | respectively is an error.
		* >> | respectively is an error.
		* double Operator back to back i.e '||', '> >', '<< >' kind of things
	4. if the input we have received has passed the above testes, we start expansion i.e:
		-> expanding any environment variable we might have in '$xxx' format -> details will be in that specific function.
	5. after that we will construct a 'complete' command that will be passed to the second part fo this project, i.e Excution.
*/
int	init_program(t_data *data)
{
	if (possible_error(data->input))
		return (1);
	if (start_lexing(data))
		return (1);
	if (operator_pipe_error(data))
		return (1);
	// if (start_expansion(data))
	// 	return (1);
	// if (start_cmd_extraction(data))
	// 	return (1);
	return (0);
}

// initialize my data
 /*
our general data struct will have;
	1, the input we read from the prompt,
	2. the command that we will construct (that goes to excution) in a double linked list format, and contains:
		a. a command that will have to find in our path or that is built-in
		b. the above command with its options,
		c. tokenized double linked list of our input, where each element is recognized for what they are.
		d. the enivironment variable, where we will get the PATH and excutable commands from.
for now we already have input, and we will initialize 2.b & 2.c as NULL, and we duplicate the ENV variable.
		-> once again, if not successfull we clean allocated memory, throw meaningful error message and exit smoothly,
 */
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
/*
in an infinite loop:
	1. read the line from STDIN using readline library,
	2. if its exit, free the data and the input and finish.
	3. then lets initialize our data struct.
		-> if not successfull, we clean what ever is allocated and we terminate our program smoothly.
	4. then, we start the parsing part of this project
		-> once again, if not successfull we clean allocated memory, throw meaningful error message and exit smoothly,
	5. if everything goes well, we add the command we read to history so we can use the up/down buttons to re-run them.
*/
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
			return (ft_error("exit", &data), 1);
		if (init_data(&data, input, envp))
			return (ft_clean_data(&data), 1);
		if (init_program(data))
			return (ft_clean_data(&data), 1);
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
	return (0);
}
