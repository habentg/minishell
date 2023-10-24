/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 02:45:44 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokenize_cmd(t_token **token_lst, char *cmd)
{
	char	**mem_arr;
	int		i;
	t_token	*token;

	i = -1;
	mem_arr = splitter(cmd);
	if (!mem_arr)
		return (1);
	i = -1;
	while (mem_arr[++i] != NULL)
	{
		token = tokenize_mem(mem_arr[i]);
		if (add_tok_back(token_lst, token))
			break ;
	}
	ft_clean_arr(mem_arr);
	return (0);
}

int	start_lexing(t_data *data)
{
	t_token	*token_lst;
	char	*inp;

	inp = one_space_setter(data->input);
	if (!inp)
		return (ft_error(ONESPACE_ALLOC_FAIL), 1);
	free(data->input);
	data->input = inp;
	token_lst = (t_token *)ft_calloc((sizeof(t_token) + 1), 1);
	if (!token_lst)
		return (ft_error(TOKENDL_ALLOC_FAIL), 1);
	token_lst = NULL;
	if (tokenize_cmd(&token_lst, data->input))
		return (ft_error(TOKENIZE_FAIL), 1);
	data->token = token_lst;
	return (0);
}
