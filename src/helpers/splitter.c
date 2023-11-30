/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:30:24 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/30 16:19:46 by hatesfam         ###   ########.fr       */
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

int	valid_key_check(char *key, int unset_flag)
{
	int	i;

	i = -1;
	if (!key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[++i])
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			continue ;
		if (key[i] == '=' && unset_flag == 0)
			continue ;
		return (0);
	}
	return (1);
}
