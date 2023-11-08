/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:20:44 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/08 05:15:32 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// | (pipe) -> baically just set the command before it pipeout to 1
void	extract_pipe(t_token **token, t_cmd **cmd_lst)
{
	if (ft_lstlast(*cmd_lst))
		ft_lstlast(*cmd_lst)->pipeout = 1;
	(*token) = (*token)->next;
}

// > (trunc) -> set the current command outfile to the
	//content of next token && the fdout to the file descriptor of the outfile.
/*
	If the specified file doesn't exist, it will be created.
	If it does exist, its contents will be replaced with the output of the command.
*/
void	extract_trunc(t_token **token, t_cmd **cmd_node)
{
	if ((*cmd_node)->iofd->outfile)
		free((*cmd_node)->iofd->outfile);
	if ((*cmd_node)->iofd->fdout != -1)
		close((*cmd_node)->iofd->fdout);
	(*cmd_node)->iofd->outfile = ft_strdup((*token)->next->str);
	(*cmd_node)->iofd->fdout = open((*cmd_node)->iofd->outfile, O_CREAT | \
		O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
	if ((*cmd_node)->iofd->fdout == -1)
		(*cmd_node)->iofd->fdout = -2;
	(*token) = (*token)->next->next;
}

// < (input redir) -> set the current command infile to the
	//content of next token && the fdin to the file descriptor of the infile.
int	extract_input_redir(t_token **token, t_cmd **cmd_node)
{
	if ((*cmd_node)->iofd->infile)
		free((*cmd_node)->iofd->infile);
	if ((*cmd_node)->iofd->fdin != -1)
		close((*cmd_node)->iofd->fdin);
	if (access((*token)->next->str, F_OK | R_OK) == -1)
	{
		(*token) = (*token)->next->next;
		(*cmd_node)->iofd->fdin = -2;
		return (file_dir_not_found((*token)->next->str), 0);
	}
	(*cmd_node)->iofd->infile = ft_strdup((*token)->next->str);
	(*cmd_node)->iofd->fdin = open((*cmd_node)->iofd->infile, O_RDONLY);
	if ((*cmd_node)->iofd->fdin == -1)
		(*cmd_node)->iofd->fdout = -2;
	(*token) = (*token)->next->next;
	return (0);
}

// >>
/*
	If the specified file doesn't exist, it will be created.
	If it does exist,  the output of the command will be added to the end
	of the existing content in the file.
*/
void	extract_append(t_token **token, t_cmd **cmd_node)
{
	if ((*cmd_node)->iofd->outfile)
		free((*cmd_node)->iofd->outfile);
	if ((*cmd_node)->iofd->fdout != -1)
		close((*cmd_node)->iofd->fdout);
	(*cmd_node)->iofd->outfile = ft_strdup((*token)->next->str);
	(*cmd_node)->iofd->fdout = open((*cmd_node)->iofd->outfile, O_CREAT | \
		O_APPEND | O_RDWR, S_IRUSR | S_IWUSR);
	if ((*cmd_node)->iofd->fdout == -1)
		(*cmd_node)->iofd->fdout = -2;
	(*token) = (*token)->next->next;
}
