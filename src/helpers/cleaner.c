/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:02:57 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/30 20:02:28 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* cleaning cmd d-linked list*/
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

/* cleaning token d-linked list*/
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

// cleaner funcs
/* at every run*/
void	ft_clean_data(t_data **data)
{
	if ((*data)->input != NULL)
		free((*data)->input);
	if ((*data)->cmd_lst != NULL)
		ft_lst_clear_cmd(&(*data)->cmd_lst);
	if ((*data)->token != NULL)
		ft_clean_tok_dl(&(*data)->token);
}

/* at exit*/
void	ft_clean_data_onexit(t_data **data)
{
	if ((*data)->envi)
		ft_clean_arr((*data)->envi);
	if ((*data)->path)
		ft_clean_arr((*data)->path);
	if (*data)
		free(*data);
	printf("exit\n");
}

/* at anytime when we are finishing up with minishell*/
void	ft_clean_data_done(t_data **data)
{
	ft_clean_data(data);
	if ((*data)->envi)
		ft_clean_arr((*data)->envi);
	if ((*data)->path)
		ft_clean_arr((*data)->path);
	if (*data)
		free(*data);
}
