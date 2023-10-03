/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:56:05 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:56:07 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_strdup(const char *s1, size_t len)
{
	char	*ret;

	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	return ((char *)ft_memmove(ret, s1, len));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	ret_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	ret_len = ft_strlen(s + start);
	if (len > ret_len)
		len = ret_len;
	ret = new_strdup(s + start, len);
	return (ret);
}

// int	main()
// {
// 	const char	s[] = "01234567";

// 	// printf("%d\n", check_size(s, 7, 7));
//     char *k;
// 	k = ft_substr(s, 7, 9);

//     for (int i = 0; i < 20; i++)
// 	{
// 		printf("%c\n", k[i]);
// 	}
//     return 0;
// }