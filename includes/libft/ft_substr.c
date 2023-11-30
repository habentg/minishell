/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:56:05 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 21:07:08 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* 
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	if (!s || len == 0)
		return (0);
	i = start;
	while (s[i] != '\0' && (i - start) < len)
		i++;
	substring = (char *)malloc((i + 1 - start) * sizeof(char));
	if (!substring)
		return (0);
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
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substr = ft_strdup("");
		return (substr);
	}
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
// int	main()
// {
// 	const char	s[] = "01234567";

//     char *k;
// 	k = ft_substr(s, 2, 6);
// 	printf("%s\n", k);
//     return 0;
// }