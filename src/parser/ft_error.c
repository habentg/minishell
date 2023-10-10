/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 03:52:52 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/10 04:34:42 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *err_msg, t_cmd **cmd_list)
{
	ft_putendl_fd(err_msg, 1);
	if (cmd_list)
		ft_clean_dl(cmd_list);
}
