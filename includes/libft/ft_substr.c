/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:56:05 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/30 18:23:34 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	if (!s || len == 0)
		return (NULL);
	i = start;
	while (s[i] != '\0' && (i - start) < len)
		i++;
	substring = (char *)malloc((i + 1 - start) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && start < ft_strlen(s) && i < len)
	{
		substring[i++] = s[start++];
	}
	substring[i] = '\0';
	return (substring);
} */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
		i++;
	substring = (char *)malloc((i + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

// int	main()
// {
// 	const char	s[] = "01234567";

//     char *k;
// 	k = ft_substr(s, 2, 6);
// 	printf("%s\n", k);
//     return 0;
// }