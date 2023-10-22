/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:49:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/22 12:15:09 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	###### for tokens between a pipe ######
	1. cmd cases
		-> if its the 1st word type
		-> if its the 1s word type after a pipe
		-> .....
 	2. cmd args cases
		* from the 'cmd' all the word type until an operator
	THEN add_back to the cmd_list.
*/

int	extract_cmdargs(t_data *data)
{
	(void)data;
	return (0);
}

int	extract_cmds(t_data *data)
{
	// t_cmds	*cmd;
	(void)data;
	// do your shit here
	// data->cmds;
	return (0);
}

int	start_cmd_extraction(t_data *data)
{
	if (extract_cmds(data))
		return (1);
	return (0);
}
