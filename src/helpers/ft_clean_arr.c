/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 05:08:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 11:14:16 by hatesfam         ###   ########.fr       */
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
}

int	arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_clean_data(t_data **data)
{
	if ((*data)->input)
		free((*data)->input);
	if ((*data)->cmd)
		ft_clean_cmd_dl(&(*data)->cmd);
	if ((*data)->token)
		ft_clean_tok_dl(&(*data)->token);
}

void	ft_clean_data_exit(t_data **data)
{
	if ((*data)->envi)
		ft_clean_arr((*data)->envi);
	free(*data);
}
