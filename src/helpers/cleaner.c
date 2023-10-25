/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:02:57 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 22:10:12 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmdnode(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmdarg)
		ft_clean_arr(cmd->cmdarg);
	if (cmd->iofd)
		free(cmd->iofd);
}

void	ft_clean_cmd_dl(t_cmd **dl)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *dl;
	next = *dl;
	while (current)
	{
		next = current->next;
		free_cmdnode(current);
		current = next;
	}
}



