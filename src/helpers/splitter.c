/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:30:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/25 20:26:07 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncmp_custom(const char *str1, const char *str2, size_t n)
{
	unsigned int		i;

	i = 0;
	while (str1[i] && i < n)
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	if (str2[i] == '\0' && str1[i] == '\0')
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
