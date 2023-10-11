/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:02:58 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/11 18:40:32 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'\
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	ft_whitespaces(char *str, int *index, char c)
{
	int	i;

	i = *index;
	if (c == 'f')
	{
		while (str[++i])
		{
			if (!is_whitespace(str[i]))
				break ;
		}
	}
	else if (c == 'b')
	{
		while (--i >= 0)
		{
			if (!is_whitespace(str[i]))
				break ;
		}	
	}
	return (i);
}

// int main(void)
// {
// 	int i = -1;
// 	printf("->%d\n", ft_whitespaces("k   haben        f", &i, 'f'));
// }