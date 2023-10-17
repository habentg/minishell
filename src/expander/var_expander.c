/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:12:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 16:10:11 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_var(t_token **token_lst)
{
	(void)token_lst;
	return (0);
}

int	start_expansion(t_data *data, char **envp)
{
	(void)envp;

	if (check_var(&data->token))
		return (1);
	return (0);
}
