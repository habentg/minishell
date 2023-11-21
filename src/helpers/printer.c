/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:45:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/21 14:51:13 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_lst(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("token->str: %s, token->type: %u\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

void	print_cmd_lst(t_cmd *cmd)
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
		if (cmd->pipe_fd)
			printf("pipe_fd: %p\n", cmd->pipe_fd);
		printf("infile: %s\n", cmd->iofd->infile);
		printf("outfile: %s\n", cmd->iofd->outfile);
		printf("fdin: %d\n", cmd->iofd->fdin);
		printf("fdout: %d\n", cmd->iofd->fdout);
		printf("----------------------------------\n");
		cmd = cmd->next;
	}
}

void	print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("arr[%d]: %s\n", i, arr[i]);
}

void	print_env_lst(t_data *data)
{
	t_env	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		printf("key: [%s]\n", tmp->key);
		printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
	printf("env_lst head: %s\n", data->env_lst->key);
}

int	ft_env_lsize(t_env *lst)
{
	int		i;
	t_env	*temp_node;

	temp_node = lst;
	i = 0;
	while (temp_node != NULL)
	{
		temp_node = temp_node->next;
		i++;
	}
	return (i);
}
