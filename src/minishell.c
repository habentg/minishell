/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:57:10 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 05:36:25 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)
{
	char	*command_buffer;

	command_buffer = NULL;
	while (1)
	{
		command_buffer = readline("Minishell-🌹> ");
		if (ft_strlen(command_buffer) > 0)
		{
			add_history(command_buffer);
			// tokenize_cmd(command_buffer);
		}
		printf("%s\n", command_buffer);
		if (!ft_strncmp(command_buffer, "exit", 4))
			return (0);
	}
	return (0);
}
