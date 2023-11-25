/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/25 20:22:03 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_arr_creator(char ***arr, char *str)
{
	int			i = 0;
	int			k = 0;
	int			arr_i = 0;

	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		k = i;
		if (is_qoute(str[i]))
		{
			while (1)
			{
				if (is_qoute(str[i]))
				{
					if (str[i + 1] && is_qoute(str[i + 1]))
					{
						i++;
						continue ;
					}
					if (!str[i + 1] || (str[i + 1] && ((is_whitespace(str[i + 1]) || is_operator(str[i+1])) && get_q_state(str, i+1) == NONE)))
					{
						i++;
						break ;
					}
				}
				i++;
			}
			(*arr)[arr_i++] = ft_substr(str, k, i - k);
		}
		else if (str[i] && is_operator(str[i]))
		{
			if (str[i] && str[i] == '>' && str[i + 1] == '>')
				i++;
			else if (str[i] && str[i] == '<' && str[i + 1] == '<')
				i++;
			i++;
			(*arr)[arr_i++] = ft_substr(str, k, i - k);
		}
		else
		{
			while (1)
			{
				if (!str[i] || (str[i] && (is_operator(str[i]) || \
					is_whitespace(str[i])) && get_q_state(str, i) == NONE))
					break ;
				i++;
			}
			(*arr)[arr_i++] = ft_substr(str, k, i - k);
		}
	}
	(*arr)[arr_i] = NULL;
}

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
	mem_arr = malloc(sizeof(char *) * (one_space_counter(cmd) + 1));
	cmd_arr_creator(&mem_arr, cmd);
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
	if (!data || !data->input)
		return (0);
	if (tokenize_cmd(&data->token, data->input))
		return (ft_error(data, TOKENIZE_FAIL, 255), 1);
	return (0);
}
