/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 05:08:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/26 18:22:30 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	voidfree(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return ;
}

void	ft_delone_token(t_token *lst, void (*del)(void*))
{
	if (lst && del && lst->str)
	{
		(del)(lst->str);
		lst->str = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
}

void	ft_free_iofile(t_iofds *iofiles)
{
	if (!iofiles)
		return ;
	if (iofiles->infile)
	{
		if (iofiles->fdin != -1)
			close(iofiles->fdin);
		free(iofiles->infile);
	}
	if (iofiles->outfile)
	{
		if (iofiles->fdout != -1)
			close(iofiles->fdout);
		free(iofiles->outfile);
	}
	if (iofiles->here_delemiter)
		free(iofiles->here_delemiter);
	free(iofiles);
}

void	ft_delone_cmd(t_cmd *lst, void (*del) (void *))
{
	if (lst->cmd)
		(*del)(lst->cmd);
	if (lst->cmdarg)
		ft_clean_arr(lst->cmdarg);
	if (lst->iofd)
		ft_free_iofile(lst->iofd);
}
