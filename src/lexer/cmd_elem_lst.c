/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_elem_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 02:46:29 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 18:48:41 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokenType	t_type(char *cmd, int end_code)
{
	t_tokenType	type;

	if (end_code == 1)
		return (END);
	else if (cmd[0] == '|' && cmd[1] == '\0')
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

t_token	*tokenize_mem(char *mem, int end_code)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (end_code == 1)
		token->str = NULL;
	token->str = ft_strdup(mem);
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	token->type = t_type(mem, end_code);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

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

int	add_tok_back(t_token **lst, t_token *token, int end_code)
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
	if (end_code == 1)
	{
		printf("end of cmd\n");
		return (1);
	}
	return (0);
}

int	ft_tokendl_size(t_token **lst)
{
	int		i;
	t_token	*temp_node;

	temp_node = *lst;
	i = 0;
	while (temp_node != NULL)
	{
		temp_node = temp_node->next;
		i++;
	}
	return (i);
}