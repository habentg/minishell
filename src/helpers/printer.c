/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:45:08 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/18 13:26:07 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("token->str: %s, token->type: %u\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}
