/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 16:06:23 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize_cmd(t_token **token_lst, char *cmd)
{
	char	**mem_arr;
	int		i;
	t_token	*token;

	i = -1;
	printf("cmd: [%s]\n", cmd);
	mem_arr = splitter(cmd);
	i = -1;
	while (mem_arr[++i] != NULL)
	{
		token = tokenize_mem(mem_arr[i], 0);
		if (mem_arr[i])
			free(mem_arr[i]);
		printf("    ~>token: %s, type: %u\n", token->str, token->type);
		if (add_tok_back(token_lst, token, 0))
			break ;
	}
	// add these token linked list to cmd linked list
	
	// free token linked list
	// ft_clean_tok_dl(token_lst);
	// *token_lst = NULL;
	free(mem_arr);
}

int	start_lexing(t_data *data, char *input, char **envp)
{
	int		i;
	// char	**cmd_arr;
	t_token	**token_lst;
	// int		arr_size;

	i = -1;
	(void)envp;
	input = one_space_setter(input);
	if (!input)
		return (1);
	// cmd_arr = ft_split(input, 124);
	// arr_size = arr_length(cmd_arr);
	token_lst = (t_token **)ft_calloc(1, sizeof(t_token *));
	if (!token_lst)
		return (1);
	*token_lst = NULL;
	tokenize_cmd(token_lst, input);
	// while (cmd_arr[++i])
	// {
	// 	if (i != 0 && i < arr_size)
	// 		tokenize_cmd(token_lst, "|");
	// 	tokenize_cmd(token_lst, cmd_arr[i]);
	// }
	// free(input);
	// ft_clean_arr(cmd_arr);
	data->token = *token_lst;
	return (0);
}
