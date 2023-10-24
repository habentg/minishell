/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:49:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/24 18:53:41 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	extract_one_cmd(t_token **token, t_cmd **cmd_lst)
{
	t_cmd	*cmd_node;

	cmd_node = new_cmd();
	while ((*token)->type != PIPE && (*token)->type != END)
	{
		if ((*token)->type == WORD)
			if (extract_word(token, &cmd_node))
				return (1);
		if ((*token)->type == TRUNC)
			extract_trunc(token, &cmd_node);
	}
	add_cmdnode_back(cmd_lst, cmd_node);
	return (0);
}

int	cmd_node_construction(t_token **token, t_cmd **cmd_lst)
{
	while ((*token)->type != END && (*token)->type != PIPE)
	{
		if (extract_one_cmd(token, cmd_lst))
			return (0);
	}
	if ((*token)->type == PIPE)
		extract_pipe(token, cmd_lst);
	if ((*token)->type != END)
		if (cmd_node_construction(token, cmd_lst))
			return (1);
	return (0);
}

// implemet a recursive function that will handle the cmd extraction until pipe
int	start_cmd_extraction(t_data *data)
{
	t_cmd	**cmd_lst;
	t_token	*end_node;

	end_node = tokenize_mem("end");
	end_node->type = END;
	cmd_lst = (t_cmd **)malloc(sizeof(t_cmd *));
	if (!cmd_lst)
		return (1);
	*cmd_lst = NULL;
	add_tok_back(&data->token, end_node);
	if (cmd_node_construction(&data->token, cmd_lst))
		return (1);
	data->cmd = *cmd_lst;
	printf("we have: %d nodes\n", ft_dlsize(data->cmd));
	print_cmd(data->cmd);
	return (0);
}
/*
iterate through the token list
	1. cmd with its potential args -> word type
		# cmd cases
			-> if its the 1st word type
			-> if its the 1s word type after a pipe
			-> last cmd is null
 		#cmd args cases
			* from the 'cmd' all the word type until an operator
		THEN add_back to the cmd_list.
	2. handle every other type as well
		-> pipe
		-> append
		-> trunc
		-> input_redir
		-> here_doc
		-> var
*/
