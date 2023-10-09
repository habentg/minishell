/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:41:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/09 05:16:40 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_newnode(t_token *token)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->token = token;
	node->prev = 0;
	node->next = 0;
	return (node);
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst != 0)
	{
		if (lst->next == 0)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_addnode_back(t_cmd **lst, t_cmd *node)
{
	if (!node)
		return ;
	if (*lst == 0)
		*lst = node;
	else
		(ft_lstlast(*lst)->next = node);
}