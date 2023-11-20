/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:49:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/20 17:48:37 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	ONE CMD Extractor
	% all the "word" types unitl redirection with be considered as cmd and its args
	% then handle the redirections
		* token after file is the file name except in here_doc (its exit delimeter)
	% we finally add the cmd node to the cmd_lst
	DONE
*/
static int	extract_one_cmd(t_data *data, t_token **token, t_cmd **cmd_lst)
{
	t_cmd	*cmd_node;

	cmd_node = new_cmd();
	while ((*token)->type != PIPE && (*token)->type != END)
	{
		if ((*token)->type == WORD)
			if (extract_word(data, token, &cmd_node))
				return (1);
		if ((*token)->type == TRUNC)
			extract_trunc(token, &cmd_node);
		if ((*token)->type == INPUT_REDIR)
			extract_input_redir(token, &cmd_node);
		if ((*token)->type == APPEND)
			extract_append(token, &cmd_node);
		if ((*token)->type == HERE_DOC)
			extract_here_doc(data, token, &cmd_node);
			// run_extract_here_doc(data, token, &cmd_node);
	}
	add_cmdnode_back(cmd_lst, cmd_node);
	return (0);
}

void	update_cmd_args(t_cmd *cmd_node)
{
	if (arr_length(cmd_node->cmdarg) <= ft_arglstsize(&cmd_node->arg_lst))
	{
		if (cmd_node->cmdarg)
			ft_clean_arr(cmd_node->cmdarg);
		cmd_node->cmdarg = arr_from_arglst(cmd_node->arg_lst);
		free_arglst(&cmd_node->arg_lst);
	}
}

/*
	CMD CONSTRUCTION
		* we consider until we reach a pipe or end as ONE cmd
		* if there is pipe we flag the last command that it has a pipe
			and we create a new command node (recursively)
		* if there is no pipe, that means we are done with our token sequence
			REMEMBER: pipe cant be the last token
*/
int	cmd_node_construction(t_data *data, t_token **token, t_cmd **cmd_lst)
{
	while ((*token)->type != END && (*token)->type != PIPE)
	{
		if (extract_one_cmd(data, token, cmd_lst))
			return (0);
	}
	if ((*token)->type == PIPE)
		extract_pipe(token, cmd_lst);
	update_cmd_args(ft_lstlast(data->cmd_lst));
	if ((*token)->type != END)
		if (cmd_node_construction(data, token, cmd_lst))
			return (1);
	return (0);
}

// implemet a recursive function that will handle 
// the cmd extraction until pipe or end
int	start_cmd_extraction(t_data *data)
{
	t_token	*end_node;
	t_token	*tmp;

	if (!data || data->token == NULL)
		return (0);
	end_node = tokenize_mem("end");
	end_node->type = END;
	add_tok_back(&data->token, end_node);
	tmp = data->token;
	if (cmd_node_construction(data, &data->token, &data->cmd_lst))
		return (ft_error(data, "cmd construction failure", 255), 1);
	data->token = tmp;
	return (0);
}
