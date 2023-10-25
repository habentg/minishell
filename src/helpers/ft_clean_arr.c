/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 05:08:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 22:42:51 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_arr(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != NULL)
			free(argv[i]);
		i++;
	}
	free(argv);
}

// void	ft_clean_tok_dl(t_token **dl)
// {
// 	t_token	*current;
// 	t_token	*next;

// 	current = *dl;
// 	next = NULL;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		if (current->str)
// 			free(current->str);
// 		free(current);
// 		current = next;
// 	}
// }

int	arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_clean_data(t_data **data)
{
	if ((*data)->input)
		free((*data)->input);
	if ((*data)->cmd)
		ft_clean_cmd_dl(&(*data)->cmd);
	if ((*data)->token)
		ft_clean_tok_dl_2(&(*data)->token, voidfree);
}

void	ft_clean_data_exit(t_data **data)
{
	if ((*data)->envi)
		ft_clean_arr((*data)->envi);
	if ((*data)->path)
		ft_clean_arr((*data)->path);
	free(*data);
}










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

void	ft_clean_tok_dl_2(t_token **lst, void (*del)(void*))
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


// static void	ft_delone_cmd(t_cmd *lst, void (*del) (void *))
// {
// 	if (lst->cmd)
// 		(*del)(lst->cmd);
// 	if (lst->tube)
// 		(*del)(lst->tube);
// 	if (lst->cmdarg)
// 		ft_arr_freer(lst->cmdarg);
// 	if (lst->iofiles)
// 		ft_free_iofile(lst->iofiles);
// }

// void	ft_lst_clear_cmd(t_cmd **lst, void (*del)(void*))
// {
// 	t_cmd	*m;

// 	if (lst && del && lst)
// 	{
// 		while (*lst)
// 		{
// 			m = (*lst)->next;
// 			ft_delone_cmd(*lst, del);
// 			free(*lst);
// 			*lst = m;
// 		}
// 	}
// }