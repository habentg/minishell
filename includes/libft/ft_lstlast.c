/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:58:44 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:58:46 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*head_node;
	t_list	*res;

	head_node = lst;
	res = NULL;
	if (!head_node)
		return (0);
	while (head_node != NULL)
	{
		res = head_node;
		head_node = head_node->next;
	}
	return (res);
}
