/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:51:34 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/23 19:34:07 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	extract_pipe(t_token **token, t_cmd **cmd_lst)
{
	(void)cmd_lst;
	(void)token;
	printf("we have pipe\n");
	ft_lstlast(*cmd_lst)->pipeout = 1;
	return (0);
}

/*
	Extracts the > operator
		* creates a new node -> default template
		
*/
int	extract_trunc(t_token **token, t_cmd **cmd_lst)
{
	t_cmd	*less_node;

	less_node = new_cmd(NULL);
	if (!less_node)
		return (1);
	less_node->iofd = new_iofds();
	if (!less_node->iofd)
		return (1);
	less_node->iofd->outfile = ft_strdup((*token)->next->str);
	less_node->iofd->fdout = open(less_node->iofd->outfile, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	// you will need to acess the last command and:
		// 1. set the iofds->outputfd to less_node->iofd->fdout
		// 2. everythin else is the NULL
	add_cmdnode_back(cmd_lst, less_node);
	printf("we almost done wit trunc\n");
	(*token) = (*token)->next->next;
	return (0);
}

// int	extract_redir(t_token **token, t_cmd **cmd_lst)
// {
// 	(void)cmd_lst;
// 	printf("we have redir\n");
// 	(*token) = (*token)->next;
// 	return (0);
// }

// int	extract_var(t_token **token, t_cmd **cmd_lst)
// {
// 	(void)cmd_lst;
// 	printf("we have var\n");
// 	(*token) = (*token)->next;
// 	return (0);
// }


