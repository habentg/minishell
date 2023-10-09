/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/09 09:25:49 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	operator_end_err(char *input)
{
	size_t	i;

	i = ft_strlen(input) - 1;
	while (input[i] == ' ' || input[i] == '\t')
		i--;
	if (input[i] == '|')
		return (ft_error(PIPE_AT_END, 0), 1);
	else if (input[i] == '>' || input[i] == '<')
		return (ft_error(REDIR_AT_END, 0), 1);
	return (0);
}

int	open_qoute_err(char *input)
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
		ft_error(UNCLOSED_QOUTE, 0);
	return (flag_s || flag_d);
}

int	possible_error(char *input)
{
	int	i;

    i = ft_whitespaces(input, &i);
	// pipe or redirection the end error
	if (operator_end_err(input))
		return (1);
	// unclosed qoutes
	if (open_qoute_err(input))
		return (1);
	return (0);
}

int	check_input_cmd(t_cmd **cmd_list, char *input)
{
	int		i;
	int		start;
	char	*cmd;

	(void)cmd_list;
	start = 0;
	i = 0;
	cmd = NULL;
	if (possible_error(input))
		return (1);
	i = ft_whitespaces(input, &i);
	while (input[i])
	{
		if (input[i] == '|')
		{
			// clip the word untill the pipe - dont forget to free
			cmd = ft_substr(input, start, (i - start + 1));
			printf("%s\n", cmd);
			// tokenize this sub (inc the pipe) create a simple comand node and linked list
			parse(cmd_list, cmd);
			
			// put a pipe as one node
			free(cmd);
			start = i + 1;
		}
		i++;
    }
	cmd = ft_substr(input, start, (i-start));
	printf("%s\n", cmd);
	free(cmd);
    return (0);
}