/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:41:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 16:02:39 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_dl(t_cmd **dl)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *dl;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	free(dl);
}

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

t_cmd	*ft_newnode(t_token *token, char *txt)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->value = ft_strdup(txt);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->token = token;
	node->prev = NULL;
	node->next = NULL;
	return (node);
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

void	ft_addnode_back(t_cmd **lst, t_cmd *node)
{
	t_cmd	*last;

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
