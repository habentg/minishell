/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:57:23 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:57:23 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int			i;
	const char	*newval;

	i = 0;
	if (c == '\0')
	{
		while (str[i] != '\0')
			i++;
		return ((char *)&str[i]);
	}
	while (*str != '\0')
	{
		while ((unsigned char)*str == (unsigned char)c)
		{
			newval = str;
			return ((char *)newval);
		}
		str++;
	}
	return (0);
}

// int main()
// {
// 	char a[50] = "helloWorld!@abudhabi.com1";
// 	char c = '@';

// 	printf("%s\n", ft_strchr(NULL, c));
// 	printf("\n %s\n", strchr(NULL, c));
// }
