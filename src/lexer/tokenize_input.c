/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 02:05:18 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 19:24:50 by hatesfam         ###   ########.fr       */
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

/*printing all content and type of the tokenized d-inked list*/
void	print_dl(t_token **dl)
{
	t_token	*node;

	node = *dl;
	printf("\n--------------\n");
    while (node)
	{
		if (node != *dl)
        	printf("prev: %s, type: %u <- ", node->prev->str, node->prev->type);
        printf("CURR: %s, type: %u", node->str, node->type);
		if (node != last_mem(*dl))
        	printf("-> next: %s, type: %u", node->next->str, node->next->type);
		node = node->next;
		printf("\n--------------\n");
	}
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
	// print_dl(token_lst);
	return (0);
}
