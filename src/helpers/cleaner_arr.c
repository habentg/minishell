/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:16:16 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/26 21:02:08 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_arr(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (argv[i] != NULL)
			free(argv[i]);
	}
	if (argv != NULL)
		free(argv);
}

int	arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
