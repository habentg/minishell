/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:41:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/09 11:16:42 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_newnode(t_token *token, char *txt)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->token = token;
	node->value = txt;
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
	t_cmd	*last;

	last = 0;
	if (!node)
		return ;
	if (*lst == 0)
		*lst = node;
	else
	{
		last = ft_lstlast(*lst);
		last->next = node;
		node->prev = last;
	}
	free(last);
}
