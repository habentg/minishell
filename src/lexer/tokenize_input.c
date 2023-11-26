/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/26 18:43:30 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	helper_operator(char ***arr, char *str, int *i, int *arr_i)
{
	int	k;

	k = *i;
	if (str[*i] && is_operator(str[*i]))
	{
		if (str[*i] && str[*i] == '>' && str[*i + 1] == '>')
			(*i)++;
		else if (str[*i] && str[*i] == '<' && str[*i + 1] == '<')
			(*i)++;
		(*i)++;
		(*arr)[(*arr_i)++] = ft_substr(str, k, *i - k);
	}
}

static void	helper_default(char ***arr, char *str, int *i, int *arr_i)
{
	int	k;

	k = *i;
	while (1)
	{
		if (!str[*i] || (str[*i] && (is_operator(str[*i]) || \
			is_whitespace(str[*i])) && get_q_state(str, *i) == NONE))
			break ;
		(*i)++;
	}
	(*arr)[(*arr_i)++] = ft_substr(str, k, *i - k);
}

void	cmd_arr_creator(char ***arr, char *str)
{
	int	i;
	int	arr_i;

	i = 0;
	arr_i = 0;
	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		if (is_qoute(str[i]))
			helper_quotes(arr, str, &i, &arr_i);
		else if (str[i] && is_operator(str[i]))
			helper_operator(arr, str, &i, &arr_i);
		else
			helper_default(arr, str, &i, &arr_i);
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
		if (!ft_strlen(mem_arr[i]))
			continue ;
		token = tokenize_mem(mem_arr[i]);
		if (!token)
			return (ft_error(NULL, TOKENIZE_FAIL, 255), 1);
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
