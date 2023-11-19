/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:05:43 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/19 07:14:14 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// get path from envi
/*
	~ match the key with the envp array
	~ if the key matches, copy the value to a new string
	~ return the path
*/
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

/*
func to populate the env linked-list
	# create a new node from the key & value pairs
	# add the node to the end of the list
*/
static void	add_env_back_start(t_data *data, char **env_node_arr)
{
	t_env	*env_node;

	if (!env_node_arr)
		return ;
	env_node = new_env_node(env_node_arr[0], env_node_arr[1]);
	if (!env_node)
		return ;
	if (!data->env_lst)
		data->env_lst = env_node;
	else
		(last_env_node(data->env_lst))->next = env_node;
}

// env_lst to arr
/*
	~ split each member of the envi and populate it in env_lst (key&value)
	~ return 0 if everything went well
*/
int	create_env_lst(t_data **data)
{
	int		i;
	char	**tmp_arr;

	i = -1;
	tmp_arr = NULL;
	while ((*data)->envi[++i])
	{
		tmp_arr = ft_split_custom((*data)->envi[i]);
		add_env_back_start(*data, tmp_arr);
		ft_clean_arr(tmp_arr);
	}
	return (0);
}

// init env path
/*
	~ get the envp array & copy it to the envi array
	~ get the path (from envi), split and put it in the path array
	~ if there is no path, create an empty path array
		-- coz our minishell can work without the path
	~ return 0 if everything went well
*/
int	init_env_path(t_data **data, char **envp)
{
	int		i;
	char	*my_path;

	i = -1;
	my_path = NULL;
	(*data)->envi = (char **)ft_calloc((sizeof(char *)), \
		(arr_length(envp) + 1));
	while (++i < arr_length(envp) && envp[i])
		(*data)->envi[i] = ft_strdup(envp[i]);
	(*data)->envi[i] = NULL;
	my_path = get_path((*data)->envi, "PATH");
	(*data)->path = ft_split(my_path, ':');
	if (my_path == NULL)
	{
		(*data)->path = (char **)malloc(sizeof(char *) * 1);
		(*data)->path[0] = NULL;
	}
	if (my_path)
		free(my_path);
	return (0);
}

// init minishell program
/*
	all minishell steps are here
			A. PARSING - PART
	1. basic error handling ->  before all the hustle
		* unclosed quotes & redirection/pipe at the end
	2. lexical analysis ->  tokenize the input
		* recognize every member of the input,
		* populate it in a linked-list
		// briefly explained in the start lexing function
	3. variable expansion ->  expand possible variables
		* playing with token linked-list
		* expand the variables i.e something with $ in it
			// $? -> exit code
			// $VALID -> replace with the value of the variable
			// $INVALID -> replace with NULL
		* removing extra qoutes, thats what bash does
		// briefly explained in the start var expantion file
	4. command extraction ->  extract the commands from the token linked-list
		NOTE: a command is a sequence of tokens separated by PIPE
		* populate the command linked-list
		* one command per node
		// briefly explained in the start cmd extraction file
		
			A. EXECUTION - PART
	5. execution ->  execute the commands
		* play with the command linked-list
		* execute the commands one by one in in their own separate process
		* wait for the child process to finish -> collect exit code
		// briefly explained inside start execution function.
*/
int	init_program(t_data *data)
{
	if (possible_error(&data))
		return (0);
	if (start_lexing(data))
		return (1);
	if (operator_pipe_error(data))
		return (0);
	if (start_expansion(data))
		return (0);
	if (start_cmd_extraction(data))
		return (1);
	if (start_execution(data))
		return (1);
	return (0);
}
