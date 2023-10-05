/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/06 02:09:42 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	char *input;

	input = NULL;
	// we dont accept any arguments ..
	if (ac != 1)
		return (1);
	// command sanitization
	input = readline("Minishell-🌹> ");
	if (!check_input_cmd(av))
		return (1);
	// lex -> tokonization
	// parse
	return (0);
}
