/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:49:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/23 04:48:29 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmdargs(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type == WORD)
	{
		token = token->next;
		i++;
	}
	return (i);
}

int	extract_cmdargs(t_token **token, t_cmd **cmd_node)
{
	int		count;
	int		i;

	i = 0;
	count = count_cmdargs(*token);
	// printf("cmd args count: %d\n", count);
	(*cmd_node)->cmdarg = (char **)ft_calloc(sizeof(char *), (count + 1));
	if (!(*cmd_node)->cmdarg)
		return (1);
	while ((*token) && (*token)->type == WORD && i < count)
	{
		// printf("~~~>cmdarg: %s\n", (*token)->str);
		(*cmd_node)->cmdarg[i] = ft_strdup((*token)->str);
		if (!(*cmd_node)->cmdarg[i++])
			return (ft_error(FAILED_TO_DUPLICATE), 1);
		(*token) = (*token)->next;
	}
	(*cmd_node)->cmdarg[count] = NULL;
	return (0);
}

int	extract_word(t_token **token, t_cmd **cmd_lst)
{
	t_cmd	*cmd_node;

	cmd_node = NULL;
	while ((*token) && (*token)->type == WORD)
	{
		// printf("#cmd: %s\n", (*token)->str);
		if ((*token)->prev == NULL || (*token)->prev->type == PIPE)
		{
			cmd_node = new_cmd((*token)->str);
			if (!cmd_node)
				return (1);
		}
		if (extract_cmdargs(token, &cmd_node))
			return (1);
		if (!(*token) || (*token)->type != WORD)
			break ;
	}
	add_cmdnode_back(cmd_lst, cmd_node);
	// printf("Done with cmd\n");
	return (0);
}
/*
iterate through the token list
	1. cmd with its potential args -> word type
		# cmd cases
			-> if its the 1st word type
			-> if its the 1s word type after a pipe
			-> .....
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

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("we have: %d nodes\n", ft_dlsize(cmd));
	while (cmd)
	{
		printf("##cmd: %s\n", cmd->cmd);
		while (cmd->cmdarg[i])
			printf("-cmdarg: %s\n", cmd->cmdarg[i++]);
		i = 0;
		cmd = cmd->next;
	}
}

int	start_cmd_extraction(t_data *data)
{
	t_cmd	**cmd_lst;
	t_token	*token;

	cmd_lst = (t_cmd **)malloc(sizeof(t_cmd *));
	if (!cmd_lst)
		return (1);
	*cmd_lst = NULL;
	token = data->token;
	while (token)
	{
		if (token->type == WORD)
		{
			if (extract_word(&token, cmd_lst))
				return (1);
		}
		if (!token)
			break ;
		token = token->next;
	}
	printf("DONE\n");
	data->cmd = *cmd_lst;
	print_cmd(*cmd_lst);
	return (0);
}

		// else if (token->type == PIPE)
		// {
		// 	if (extract_pipe(&token, cmd_lst))
		// 		return (1);
		// }
		// else if (token->type == TRUNC)
		// {
		// 	if (extract_trunc(&token, cmd_lst))
		// 		return (1);
		// }
		// else if (token->type == APPEND)
		// {
		// 	if (extract_append(&token, cmd_lst))
		// 		return (1);
		// }
		// else if (token->type == INPUT_REDIR)
		// {
		// 	if (extract_input_redir(&token, cmd_lst))
		// 		return (1);
		// }
		// else if (token->type == HERE_DOC)
		// {
		// 	if (extract_here_doc(&token, cmd_lst))
		// 		return (1);
		// }
		// else if (token->type == VAR)
		// {
		// 	if (extract_var(&token, cmd_lst))
		// 		return (1);
		// }
