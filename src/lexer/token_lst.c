/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 02:46:29 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/29 17:40:16 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	token type identifier -> enumerated in minishell.h
*/
t_tokenType	t_type(char *cmd)
{
	t_tokenType	type;

	if (cmd[0] == '|' && cmd[1] == '\0')
		type = PIPE;
	else if ((cmd[0] == '>' || cmd[0] == '<'))
	{
		type = INPUT_REDIR;
		if (cmd[0] == '>')
			type = TRUNC;
		if (is_heredoc_append(cmd, 0, cmd[0]) != 0)
		{
			type = APPEND;
			if (is_heredoc_append(cmd, 0, cmd[0]) == 1)
				type = HERE_DOC;
		}
	}
	else if (cmd[0] == '$')
		type = VAR;
	else
		type = WORD;
	return (type);
}

/*
	new token initializer
*/
t_token	*tokenize_mem(char *mem)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(mem);
	if (!token->str)
		token->str = NULL;
	token->type = t_type(mem);
	token->was_mpty_before = 1;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/*
	last token node finder
*/
t_token	*last_mem(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

/*
	add token node to the end of the token list
*/
int	add_tok_back(t_token **lst, t_token *token)
{
	t_token	*last;

	if (!token)
		return (1);
	if (*lst == NULL)
	{
		*lst = token;
	}
	else
	{
		last = last_mem(*lst);
		last->next = token;
		token->prev = last;
	}
	return (0);
}

/*
	token list size
*/
int	ft_tokendl_size(t_token **lst)
{
	int		i;
	t_token	*temp_node;

	temp_node = *lst;
	i = 0;
	if (!temp_node)
		return (0);
	while (temp_node != NULL)
	{
		temp_node = temp_node->next;
		i++;
	}
	return (i);
}
