/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:51:34 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/23 04:14:39 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	extract_pipe(t_token **token, t_cmd **cmd_lst)
{
	(void)cmd_lst;
	(void)token;
	printf("we have pipe\n");
	// (*token) = (*token)->next;
	return (0);
}

int	extract_redir(t_token **token, t_cmd **cmd_lst)
{
	(void)cmd_lst;
	printf("we have redir\n");
	(*token) = (*token)->next;
	return (0);
}

int	extract_var(t_token **token, t_cmd **cmd_lst)
{
	(void)cmd_lst;
	printf("we have var\n");
	(*token) = (*token)->next;
	return (0);
}

