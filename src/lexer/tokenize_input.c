/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/17 04:48:10 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	TOKENIZER
	% split the one spaced input into an array of strings
	% loop through the array and tokenize (assign a type to) each string
	% add the token to the end of the token linked-list
	% clean the array and gtfo
*/
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

/*
	LEXICAL ANALYSIS
	~ remove all the extra spaces
	~ add a space before and after the pipe/redirects/qouted values ...
	~ > TO THE TOKENIZER FUNCTION
*/
int	start_lexing(t_data *data)
{
	char	*inp;

	inp = one_space_setter(data->input);
	free(data->input);
	if (!inp)
		return (ft_error(data, ONESPACE_ALLOC_FAIL, 255), 1);
	data->input = inp;
	if (tokenize_cmd(&data->token, data->input))
		return (ft_error(data, TOKENIZE_FAIL, 255), 1);
	return (0);
}
