/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/11 18:50:46 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	operator_end_err(char *input, t_cmd **cmd_list)
{
	size_t	i;

	i = ft_strlen(input) - 1;
	while (input[i] == ' ' || input[i] == '\t')
		i--;
	if (input[i] == '|')
		return (ft_error(PIPE_AT_END, cmd_list), 1);
	else if (input[i] == '>' || input[i] == '<')
		return (ft_error(REDIR_AT_END, cmd_list), 1);
	return (0);
}

int	open_qoute_err(char *input, t_cmd **cmd_list)
{
	bool	flag_s;
	bool	flag_d;
	int		i;

	flag_s = false;
	flag_d = false;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' && !flag_d)
			flag_s = !flag_s;
		else if (input[i] == '\"' && !flag_s)
			flag_d = !flag_d;
	}
	if (flag_s || flag_d)
		ft_error(UNCLOSED_QOUTE, cmd_list);
	return (flag_s || flag_d);
}

int	possible_error(char *input, t_cmd **cmd_list)
{
	if (operator_end_err(input, cmd_list))
		return (1);
	if (open_qoute_err(input, cmd_list))
		return (1);
	return (0);
}

int	check_input_cmd(t_cmd **cmd_list, char *input)
{
	int		i;
	int		start;
	int		end;
	char	*cmd;

	i = -1;
	i = ft_whitespaces(input, &i, 'f');
	// remove extra whitespaces (insert one if there is none) between  
	if (possible_error(input, cmd_list))
		return (1);
	start = i;
	end = start;
	while (1)
	{
		if (input[i] == '|')
		{
			end = ft_whitespaces(input, &i, 'b');
			// clip the word untill the pipe - dont forget to free
			cmd = ft_substr(input, start, (end - start + 1));
			// tokenize this sub (inc the pipe) create a simple comand node and linked list
			tokenize_cmd(cmd_list, cmd);
			// put a this cmd as a as one node
			printf("->%s\n", "|");
			// tokenize_pipe(cmd_list, "|");
			// put a pipe as one node
			i = ft_whitespaces(cmd, &i, 'f');
			start = i;
			free(cmd);
		}
		if (i == ((int)ft_strlen(input)))
			break ;
		i++;
	}
	i = ft_whitespaces(cmd, &i, 'b');
	cmd = ft_substr(input, start, (i - start + 1));
	tokenize_cmd(cmd_list, cmd);
	free(cmd);
	return (0);
}


// "  abcde   |"
// "0123456789"

//6 - 2 + 1