/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:57:50 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/09 11:18:45 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_tokenize(char *cmd)
{
	t_token	*token;

	if (cmd[0] == '|' && cmd[1] == '\0')
	{
		token->type = PIPE;
		token->len = 1;
		token->state = NORMAL;
	}
	else if ((cmd[0] == '>' || cmd[0] == '<') && cmd[1] == '\0')
	{
		token->type = INPUT_REDIR;
		if (cmd[0] == '>')
			token->type = TRUNC;
		token->len = 1;
		token->state = NORMAL;
	}
	else if (cmd[0] == '>' && cmd[1] == '>' && cmd[2] == '\0')
	{
		token->type = APPEND;
		token->len = 2;
		token->state = NORMAL;
	}
	else if (cmd[0] == '<' && cmd[1] == '<' && cmd[2] == '\0')
	{
		token->type = HERE_DOC;
		token->len = 2;
		token->state = NORMAL;
	}
	else
	{
		token->type = WRD;
		token->len = ft_strlen(cmd);
		token->state = NORMAL;
	}
	return (token);
}

void	parse(t_cmd **cmd_lst, char *cmd)
{
	int	i = -1;
	int start = 0;
	t_token	*token;
	t_cmd	*node;

	token = 0;
	while (cmd[++i])
	{
		if (is_whitespace(cmd[i]) || is_operator(cmd[i]))
		{
			cmd = ft_substr(cmd, start, (i - start));
			token = ft_tokenize(cmd);
			node = ft_newnode(token, cmd);
			ft_addnode_back(cmd_lst, node);
			// if ()
			free(cmd);
			start = i + 1;
		}
	}
}
