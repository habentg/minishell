/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/12 13:02:46 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_input_cmd(t_cmd **cmd_list, char *input)
{
	int		i;
	char	**cmd_arr;
	t_token	**token_dlist;

	i = 0;
	input = ft_strdup(one_space_setter(input));
	free(one_space_setter(input));
	if (possible_error(input, cmd_list))
		return (1);
	cmd_arr = ft_split(input, 124);
	token_dlist = (t_token *)ft_calloc(1, sizeof(t_token));
	token_dlist = NULL;
	while (cmd_arr[i])
	{
		if (i != 0)
			printf("ONE COMMAND: [%s]\n", "|");
		tokenize_cmd(token_dlist, cmd_arr[i++]);
	}
	free(cmd_arr);
	return (0);
}
