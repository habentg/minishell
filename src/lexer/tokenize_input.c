/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 11:06:32 by hatesfam         ###   ########.fr       */
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
	free(mem_arr);
}

int	check_input_cmd(t_cmd **cmd_list, char *input, char **envp)
{
	int		i;
	char	**cmd_arr;
	t_token	**token_lst;
	int		arr_size;

	i = -1;
	(void)envp;
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
