/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:58:02 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:58:02 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		count;
	char		*newdest;
	const char	*newsrc;

	count = 0;
	newdest = (char *)dest;
	newsrc = (const char *)src;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (n > 0 && newsrc < newdest)
	{
		newdest[n - 1] = newsrc[n - 1];
		n--;
	}
	if (src >= dest)
	{
		while (count < n)
		{
			newdest[count] = newsrc[count];
			count++;
		}
	}
	return (dest);
}

// int main(void)
// {
//     char    dest[] = "hello";
//     const char src[] = "world";

//     ft_memmove(dest + 2, src, 3);
//     for (int i = 0; i < 15; i++)
//     {
//         printf("%c", dest[i]);
//     }
// }
