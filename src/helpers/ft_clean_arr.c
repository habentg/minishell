/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 05:08:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/14 18:30:09 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_arr(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != NULL)
			free(argv[i]);
		i++;
	}
	free(argv);
}

void	ft_clean_tok_dl(t_token **dl)
{
	t_token	*current;
	t_token	*next;

	current = *dl;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = next;
	}
	free(dl);
}


int	arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
