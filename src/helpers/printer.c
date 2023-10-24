/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:45:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/24 18:54:53 by hatesfam         ###   ########.fr       */
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
	while (cmd)
	{
		i = 0;
		printf("----------------------------------\n");
		printf("cmd: %s\n", cmd->cmd);
		printf("cmdarg: ");
		while (cmd->cmdarg[i])
			printf("%s ", cmd->cmdarg[i++]);
		printf("\n");
		printf("pipeout: %d\n", cmd->pipeout);
		printf("infile: %s\n", cmd->iofd->infile);
		printf("outfile: %s\n", cmd->iofd->outfile);
		printf("fdin: %d\n", cmd->iofd->fdin);
		printf("fdout: %d\n", cmd->iofd->fdout);
		printf("----------------------------------\n");
		cmd = cmd->next;
	}
}
