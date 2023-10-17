/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:45:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 19:46:25 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("str: %s, type: %u\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}
