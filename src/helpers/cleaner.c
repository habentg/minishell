/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:02:57 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/25 23:17:53 by hatesfam         ###   ########.fr       */
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

//Used for closing file_descriptors after every run
static void close_all_file_descriptors(t_cmd *cmd_lst) 
{
    t_cmd *tmp_cmd = cmd_lst;

    while (tmp_cmd)
	{
        if (tmp_cmd->pipe_fd)
		{
            close(tmp_cmd->pipe_fd[0]);
            close(tmp_cmd->pipe_fd[1]);
        }
        tmp_cmd = tmp_cmd->next;
    }
}

// cleaner funcs
/* at every run*/
void	ft_clean_data(t_data **data)
{
	close_all_file_descriptors((*data)->cmd_lst);
	if ((*data)->input != NULL)
		free((*data)->input);
	if ((*data)->cmd_lst != NULL)
		ft_lst_clear_cmd(&(*data)->cmd_lst);
	if ((*data)->token != NULL)
		ft_clean_tok_dl(&(*data)->token);
}


/* at anytime when we are finishing up with minishell*/
void	ft_clean_data_done(t_data **data, int code)
{
	g_exit_status = (*data)->exit_code;
	if (code == 1)
		ft_clean_data(data);
	if (code == 2)
	{
		g_exit_status = 0;
		ft_putendl_fd("exit", 1);
	}
	if ((*data)->envi)
		ft_clean_arr((*data)->envi);
	if ((*data)->path)
		ft_clean_arr((*data)->path);
	if ((*data)->env_lst != NULL)
		free_env_lst(*data);
	if ((*data)->cwd)
		free((*data)->cwd);
	if (*data)
		free(*data);
	exit (g_exit_status);
}

