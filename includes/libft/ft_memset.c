/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:57:56 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:57:56 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int val, size_t n)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)dest;
	while (i < n)
	{
		p[i] = val;
		i++;
	}
	dest = p;
	return (dest);
}

// int main(void)
// {
// 	char    dest[20];
// 	char *p = ft_memset(dest, 'a', 10);
// 	printf("%p\n", p);
// 	for(size_t i = 0; i < ft_strlen(p); i++)
// 		printf("%c\n", p[i]);
// 	printf("%p\n", memset(dest, 'a', 20));   
// }
