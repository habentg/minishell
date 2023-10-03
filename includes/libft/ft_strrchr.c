/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:56:22 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:56:22 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*p;

	p = 0;
	while (*str)
	{
		if (*str == (unsigned char)c)
			p = ((char *)str);
		str++;
	}
	if (!c)
		p = ((char *)str);
	return (p);
}

// int	main(void)
// {
// 	char	str[] = "this-is-a-test-string";
// 	char	c = '-';

// 	printf("strrchr func:%s\n", strrchr(str, c));
// 	printf("ft_strrchr func: %s\n", ft_strrchr(str, c));
// }