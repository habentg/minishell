/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:41:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/03 06:53:25 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_dlsize(t_cmd *lst)
{
	int		i;
	t_cmd	*temp_node;

	temp_node = lst;
	i = 0;
	while (temp_node != NULL)
	{
		temp_node = temp_node->next;
		i++;
	}
	return (i);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd_node;

	cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_node)
		return (NULL);
	cmd_node->cmd = NULL;
	cmd_node->cmdarg = NULL;
	cmd_node->pipeout = 0;
	cmd_node->iofd = new_iofds();
	cmd_node->pipe_fd = NULL;
	cmd_node->next = NULL;
	cmd_node->prev = NULL;
	cmd_node->cmd_exit_status = 0;
	return (cmd_node);
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	add_cmdnode_back(t_cmd **lst, t_cmd *node)
{
	t_cmd	*last;

	if (!node)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		last = ft_lstlast(*lst);
		last->next = node;
		node->prev = last;
	}
}
