/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/19 17:54:16 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize_cmd(t_token **token_lst, char *cmd)
{
	char	**mem_arr;
	int		i;
	t_token	*token;

	i = -1;
	mem_arr = splitter(cmd);
	i = -1;
	while (mem_arr[++i] != NULL)
	{
		token = tokenize_mem(mem_arr[i], 0);
		if (mem_arr[i])
			free(mem_arr[i]);
		if (add_tok_back(token_lst, token, 0))
			break ;
	}
	free(mem_arr);
}

int	start_lexing(t_data *data, char *input)
{
	int		i;
	t_token	**token_lst;

	i = -1;
	input = one_space_setter(input);
	if (!input)
		return (1);
	token_lst = (t_token **)ft_calloc(1, sizeof(t_token *));
	if (!token_lst)
		return (1);
	*token_lst = NULL;
	tokenize_cmd(token_lst, input);
	data->token = *token_lst;
	// print_token(data->token);
	return (0);
}
