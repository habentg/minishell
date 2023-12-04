/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:57:00 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:57:00 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*temp_dst;
	char	*temp_src;
	size_t	dst_length;
	size_t	buffer;

	temp_dst = dst;
	temp_src = (char *)src;
	buffer = dstsize;
	while (buffer-- != 0 && *temp_dst != '\0')
		temp_dst++;
	dst_length = temp_dst - dst;
	buffer = dstsize - dst_length;
	if (buffer == 0)
		return (dst_length + ft_strlen(temp_src));
	while (*temp_src != '\0')
	{
		if (buffer > 1)
		{
			*temp_dst++ = *temp_src;
			buffer--;
		}
		temp_src++;
	}
	*temp_dst = '\0';
	return (dst_length + (temp_src - src));
}

// int main(void)
// {
//     char    dest[10] = "xx";
//     const char src[256] = "hello world";
//     printf("%zu\n", ft_strlcat(dest, src, 1));
// 	printf("%zu\n", strlcat(dest, src, 1));
// }