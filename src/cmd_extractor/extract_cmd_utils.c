/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:51:34 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/24 19:18:45 by hatesfam         ###   ########.fr       */
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
	(*cmd_node)->cmdarg = (char **)ft_calloc(sizeof(char *), (count + 1));
	if (!(*cmd_node)->cmdarg)
		return (1);
	while ((*token) && (*token)->type == WORD && i < count)
	{
		(*cmd_node)->cmdarg[i] = ft_strdup((*token)->str);
		if (!(*cmd_node)->cmdarg[i++])
			return (ft_error(FAILED_TO_DUPLICATE), 1);
		if ((*token)->type == END)
			return (0);
		(*token) = (*token)->next;
	}
	return (0);
}

int	extract_word(t_token **token, t_cmd **cmd_node)
{
	while ((*token) && (*token)->type == WORD)
	{
		if ((*token)->prev == NULL || (*token)->prev->type == PIPE)
		{
			(*cmd_node)->cmd = ft_strdup((*token)->str);
			if (!(*cmd_node)->cmd)
				return (1);
		}
		if (extract_cmdargs(token, cmd_node))
			return (1);
		if (!(*token) || (*token)->type != WORD)
			return (0);
	}
	return (0);
}

void	extract_pipe(t_token **token, t_cmd **cmd_lst)
{
	ft_lstlast(*cmd_lst)->pipeout = 1;
	(*token) = (*token)->next;
}

void	extract_trunc(t_token **token, t_cmd **cmd_node)
{
	(*cmd_node)->iofd->outfile = ft_strdup((*token)->next->str);
	(*cmd_node)->iofd->fdout = open((*cmd_node)->iofd->outfile, O_CREAT | \
		O_RDWR, S_IRUSR | S_IWUSR);
	(*token) = (*token)->next->next;
}

// int	extract_redir(t_token **token, t_cmd **cmd_lst)
// {
// 	(void)cmd_lst;
// 	printf("we have redir\n");
// 	(*token) = (*token)->next;
// 	return (0);
// }
