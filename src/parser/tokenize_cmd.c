/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:57:50 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/10 06:11:12 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_tokenize(char *cmd)
{
	t_token	*token;

	token = 0;
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

void	tokenize_cmd(t_cmd **cmd_lst, char *cmd)
{
	int	i = 0;
	int start = 0;
	t_token	*token;
	// t_cmd	*node;
	char *str;

	token = 0;
	(void)cmd_lst;
	str = 0;
	printf("--------\n");
	printf("%s\n", cmd);
	while (cmd[i])
	{
		if (is_whitespace(cmd[i]) || is_operator(cmd[i]))
		{
			str = ft_substr(cmd, start, (i - start + 1));
			printf("->%s\n", str);
			// token = ft_tokenize(str);
			// node = ft_newnode(token, str);
			// ft_addnode_back(cmd_lst, node);
			// // if ()
			free(str);
			i = ft_whitespaces(cmd, &i, 'f');
			start = i;
		}
		i++;
	}
	str = ft_substr(cmd, start, (i - start + 1));
	printf("->%s\n", str);
	free(str);
	printf("--------\n");
}
