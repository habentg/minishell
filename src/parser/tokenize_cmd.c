/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:57:50 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/12 02:32:14 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

t_token	*ft_tokenize(char *cmd)
{
	t_token	*token;

	token = 0;
	if (cmd[0] == '|' && cmd[1] == '\0')
	{
		token->type = PIPE;
		token->len = 1;
	}
	else if ((cmd[0] == '>' || cmd[0] == '<') && cmd[1] == '\0')
	{
		token->type = INPUT_REDIR;
		if (cmd[0] == '>')
			token->type = TRUNC;
		token->len = 1;
	}
	else if (cmd[0] == '>' && cmd[1] == '>' && cmd[2] == '\0')
	{
		token->type = APPEND;
		token->len = 2;
	}
	else if (cmd[0] == '<' && cmd[1] == '<' && cmd[2] == '\0')
	{
		token->type = HERE_DOC;
		token->len = 2;
	}
	else
	{
		token->type = WRD;
		token->len = ft_strlen(cmd);
	}
	return (token);
}

void	tokenize_cmd(t_cmd **cmd_lst, char *cmd)
{
	char	**arr;
	int		c;

	(void)cmd_lst;
	c = 0;
	printf("ONE COMMAND: [%s]\n", cmd);
	arr = ft_split(cmd, 32);
	while (arr[c])
		printf ("->'%s'\n", arr[c++]);
}
