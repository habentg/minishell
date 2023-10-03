/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:56:28 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:56:28 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0' || little == NULL)
		return ((char *)big);
	while ((i < len) && (big[i] != '\0'))
	{
		j = 0;
		while (((big[i + j] == little[j])
				&& (i + j < len)))
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
// int	main(void)
// {
// 	char    big[] = "ABCDEFG-haben-HIJKLM";
//     char    small[] = "haben";

//     printf("%p\n", ft_strnstr(big, small, 15));
// }