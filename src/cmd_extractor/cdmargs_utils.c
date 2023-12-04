/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdmargs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:59:17 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/20 17:16:20 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_arglstsize(t_args **lst)
{
	int		i;
	t_args	*arg_node;

	arg_node = *lst;
	i = 0;
	if (!arg_node)
		return (0);
	while (arg_node)
	{
		i++;
		arg_node = arg_node->next;
	}
	return (i);
}

t_args	*last_arg(t_args *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_args	*args_node(char *str)
{
	t_args	*arg_node;

	arg_node = (t_args *)malloc(sizeof(t_args));
	if (!arg_node)
		return (NULL);
	arg_node->arg = ft_strdup(str);
	arg_node->next = NULL;
	return (arg_node);
}

int	add_arglst_back(t_args **lst, char *arg)
{
	t_args	*new_node;

	new_node = args_node(arg);
	if (!new_node)
		return (1);
	if (!*lst)
	{
		*lst = new_node;
	}
	else
	{
		last_arg(*lst)->next = new_node;
	}
	return (0);
}

char	**arr_from_arglst(t_args *args_lst)
{
	int		i;
	char	**arr;
	t_args	*temp_node;

	i = 0;
	temp_node = args_lst;
	arr = (char **)ft_calloc(sizeof(char *), (ft_arglstsize(&args_lst) + 1));
	if (!arr)
		return (NULL);
	while (temp_node)
	{
		arr[i] = ft_strdup(temp_node->arg);
		temp_node = temp_node->next;
		i++;
	}
	return (arr);
}
