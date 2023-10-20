/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:41:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/19 17:31:28 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_dl(t_cmds **dl)
{
	t_cmds	*current;
	t_cmds	*next;

	current = *dl;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		// free(current->value);
		free(current);
		current = next;
	}
	free(dl);
}

int	ft_dlsize(t_cmds *lst)
{
	int		i;
	t_cmds	*temp_node;

	temp_node = lst;
	i = 0;
	while (temp_node != NULL)
	{
		temp_node = temp_node->next;
		i++;
	}
	return (i);
}

t_cmds	*ft_newnode(char *txt)
{
	t_cmds	*node;

	node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	node->cmds = ft_strdup(txt);
	if (!node->cmds)
	{
		free(node);
		return (NULL);
	}
	node->cmdarg = NULL;
	node->iofd = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_cmds	*ft_lstlast(t_cmds *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_addnode_back(t_cmds **lst, t_cmds *node)
{
	t_cmds	*last;

	if (!node)
		return ;
	if (*lst == NULL)
	{
		*lst = node;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = node;
		node->prev = last;
	}
}
