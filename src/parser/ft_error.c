/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 03:52:52 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/09 05:17:15 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean(t_cmd **lst)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	ft_error(char *err_msg, t_cmd **cmd_list)
{
	ft_putendl_fd(err_msg, 1);
	if (cmd_list)
		ft_clean(cmd_list);
	free(cmd_list);
}
