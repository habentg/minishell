/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:41:46 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/12 13:15:01 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h> // For strdup

// typedef struct s_cmd
// {
// 	char			*value;
// 	struct s_cmd	*next;
// 	struct s_cmd	*prev;
// }					t_cmd;

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

// int main(void)
// {
//     t_cmd *node;
//     t_cmd **dl;
//     char *arr[] = {"H", "A", "B", "E", "N", "0123456789"};
//     dl = (t_cmd **)malloc(sizeof(t_cmd *));
//     *dl = NULL;
//     for (int i = 0; i < 6; i++)
//     {
//         node = ft_newnode(arr[i]);
//         ft_addnode_back(dl, node);
//     }
//     printf("\n=>dl - size: %d\n", ft_dlsize(*dl));
// 	node = *dl;
//     while (node)
// 	{
// 		if (node != *dl)
//         	printf("prev: %s <- ", node->prev->value);
//         printf("curr: %s -> ", node->value);
// 		if (node != ft_lstlast(*dl))
//         	printf("next: %s", node->next->value);
// 		node = node->next;
// 		printf("\n--------------\n");
// 	}
// 	ft_clean_dl(dl);
//     return 0;
// }