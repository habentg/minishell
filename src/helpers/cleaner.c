/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:02:57 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/28 21:57:44 by hatesfam         ###   ########.fr       */
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
		ft_free_iofile(cmd->iofd);
}

void	ft_lst_clear_cmd(t_cmd **lst)
{
	t_cmd	*m;

	if (lst && *lst)
	{
		while (*lst)
		{
			m = (*lst)->next;
			free_cmdnode(*lst);
			free(*lst);
			*lst = m;
		}
	}
}

void	ft_clean_tok_dl(t_token **lst)
{
	t_token	*m;

	if (lst && *lst)
	{
		while (*lst)
		{
			m = (*lst)->next;
			ft_delone_token(*lst);
			free(*lst);
			*lst = m;
		}
	}
}

// new cleaner funcs
void	ft_clean_data(t_data **data)
{
	if ((*data)->input)
		free((*data)->input);
	if ((*data)->cmd)
		ft_lst_clear_cmd(&(*data)->cmd);
	if ((*data)->token)
		ft_clean_tok_dl(&(*data)->token);
}

void	ft_clean_data_exit(t_data **data)
{
	if ((*data)->envi)
		ft_clean_arr((*data)->envi);
	if ((*data)->path)
		ft_clean_arr((*data)->path);
	if (*data)
		free(*data);
}
