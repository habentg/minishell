/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:57:50 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/11 18:50:15 by hatesfam         ###   ########.fr       */
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
	// int end = 0;
	// t_token	*token;
	// t_cmd	*node;
	char *str;

	// token = 0;
	(void)cmd_lst;
	printf("--------\n");
	printf("%s\n", cmd);
	i = -1;
	i = ft_whitespaces(cmd, &i, 'f');
	start = i;
	while (1)
	{
		if (is_whitespace(cmd[i]) || is_operator(cmd[i]))
		{
			// if (is_operator(cmd[i]))
				// tokenize_redir()
			str = ft_substr(cmd, start, (i - start));
			printf("->'");
			printf("%s", str);
			printf("'\n");
			// token = ft_tokenize(str);
			// node = ft_newnode(token, str);
			// ft_addnode_back(cmd_lst, node);
			// // if ()
			i = ft_whitespaces(cmd, &i, 'f');
			start = i;
			free(str);
		}
		if (i == ((int)ft_strlen(cmd)))
			break ;
		i++;
	}
	i = ft_whitespaces(cmd, &i, 'b');
	str = ft_substr(cmd, start, (i - start + 1));
	printf("->'");
	printf("%s", str);
	printf("'\n");
	free(str);
	printf("--------\n");
}
