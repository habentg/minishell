/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:20:44 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/24 20:56:46 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	extract_pipe(t_token **token, t_cmd **cmd_lst)
{
	if (ft_lstlast(*cmd_lst))
		ft_lstlast(*cmd_lst)->pipeout = 1;
	(*token) = (*token)->next;
}

void	extract_trunc(t_token **token, t_cmd **cmd_node)
{
	(*cmd_node)->iofd->outfile = ft_strdup((*token)->next->str);
	(*cmd_node)->iofd->fdout = open((*cmd_node)->iofd->outfile, O_CREAT | \
		O_RDWR, S_IRUSR | S_IWUSR);
	close((*cmd_node)->iofd->fdout);
	(*token) = (*token)->next->next;
}

int	extract_input_redir(t_token **token, t_cmd **cmd_node)
{
	if (access((*token)->next->str, F_OK) == -1)
	{
		(*token) = (*token)->next->next;
		return (ft_error(FAILED_TO_OPEN_INPUT_FILE), -1);
	}
	(*cmd_node)->iofd->infile = ft_strdup((*token)->next->str);
	(*cmd_node)->iofd->fdin = open((*cmd_node)->iofd->infile, O_RDONLY);
	(*token) = (*token)->next->next;
	return (0);
}
