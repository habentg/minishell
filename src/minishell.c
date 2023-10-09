/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/09 02:30:28 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	char	*input;

	input = NULL;
	(void)av; /// think about it later
	if (ac != 1)
		return (1);
	while (1)
	{
		input = readline("Haben-🌹~> ");
		if (check_input_cmd(input))
			return (1);
		if (strlen(input) > 0)
			add_history(input);
	}
	return (0);
}
