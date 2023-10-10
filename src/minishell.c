/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/10 03:51:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// program entry
int	main(int ac, char **av)
{
	char	*input;
	t_cmd	**cmd_list;

	(void)av;
	input = NULL;
	cmd_list = NULL;
	if (ac != 1)
		return (1);
	cmd_list = (t_cmd **)ft_calloc(1, sizeof(t_cmd *));
	while (1)
	{
		input = readline("Haben-[:)$ ");
		if (check_input_cmd(cmd_list, input))
			return (1);
		if (strlen(input) > 0)
			add_history(input);
	}
	return (0);
}
