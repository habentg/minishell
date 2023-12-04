/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:56:34 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:56:34 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
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
	if (str2[i] == '\0' || i == n)
		return (0);
	else
		return (-str2[i]);
}

// int	main(void)
// {
// 	printf("ft_strncmp : %d\n", ft_strncmp("testxxx", "testxxxxxx", 10));
// 	printf("strncmp : %d\n", strncmp("testss", "testssssss", 10));
// }
