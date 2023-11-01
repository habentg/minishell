/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:45:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/01 09:48:34 by hatesfam         ###   ########.fr       */
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
		if (cmd->cmdarg)
			while (cmd->cmdarg[i] != NULL)
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

int	ft_strncmp_custom(const char *str1, const char *str2, size_t n)
{
	unsigned int		i;

	i = 0;
	while (str1[i] && i < n)
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	if (str2[i] == '\0' && str1[i] == '\0')
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

void	print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("arr[%d]: %s\n", i, arr[i]);
}

void	cmd_not_found(char *cmd)
{
	printf("minishell: %s: command not found\n", cmd);
}
