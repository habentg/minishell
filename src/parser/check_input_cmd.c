/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/16 12:00:45 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_input_cmd(t_cmd **cmd_list, char *input)
{
	int		i;
	char	**cmd_arr;
	t_token	**token_lst;
	int		arr_size;

	i = -1;
	if (possible_error(input, cmd_list))
		return (1);
	input = one_space_setter(input);
	cmd_arr = ft_split(input, 124);
	arr_size = arr_length(cmd_arr);
	token_lst = (t_token **)ft_calloc(1, sizeof(t_token *));
	*token_lst = NULL;
	while (cmd_arr[++i])
	{
		if (i != 0 && i < arr_size)
			tokenize_cmd(token_lst, "|");
		tokenize_cmd(token_lst, cmd_arr[i]);
	}
	ft_clean_arr(cmd_arr);
	return (0);
}
