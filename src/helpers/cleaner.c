/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:02:57 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/26 18:44:28 by hatesfam         ###   ########.fr       */
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

void	ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*))
{
	t_cmd	*m;

	if (lst && del && lst)
	{
		while (*lst)
		{
			m = (*lst)->next;
			ft_delone_cmd(*lst, del);
			free(*lst);
			*lst = m;
		}
	}
}

void	ft_clean_tok_dl(t_token **lst, void (*del)(void*))
{
	t_token	*m;

	if (lst && del && lst)
	{
		while (*lst)
		{
			m = (*lst)->next;
			ft_delone_token(*lst, del);
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
		ft_lst_clear_cmd(&(*data)->cmd, &voidfree);
	if ((*data)->token)
		ft_clean_tok_dl(&(*data)->token, &voidfree);
}

void	ft_clean_data_exit(t_data **data)
{
	if ((*data)->envi)
		ft_clean_arr((*data)->envi);
	if ((*data)->path)
		ft_clean_arr((*data)->path);
	free(*data);
}
