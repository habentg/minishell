/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:45:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/23 18:43:39 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("token->str: %s, token->type: %u\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("we have: %d nodes\n", ft_dlsize(cmd));
	while (cmd)
	{
		printf("##cmd: %s, pipeout: %d\n", cmd->cmd, cmd->pipeout);
		while (cmd->cmdarg[i])
			printf("-cmdarg: %s\n", cmd->cmdarg[i++]);
		i = 0;
		cmd = cmd->next;
	}
}