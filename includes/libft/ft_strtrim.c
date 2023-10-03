/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:56:14 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:56:16 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	getfirst(const char *str1, const char *set)
{
	size_t	count;
	size_t	len;

	count = 0;
	len = ft_strlen(str1);
	while (count < len)
	{
		if (ft_strchr(set, str1[count]) == 0)
			break ;
		count++;
	}
	return (count);
}

int	getlast(const char *str1, const char *set)
{
	size_t	count;
	size_t	len;

	count = 0;
	len = ft_strlen(str1);
	while (count < len)
	{
		if (ft_strchr(set, str1[len - count - 1]) == 0)
			break ;
		count++;
	}
	return (len - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	char	*trimmedstr;

	if (!s1)
		return (0);
	start = getfirst(s1, set);
	len = getlast(s1, set);
	if (len <= start)
		return (ft_strdup(""));
	trimmedstr = (char *)malloc(sizeof(char) * (len - start + 1));
	if (!trimmedstr)
		return (NULL);
	ft_strlcpy(trimmedstr, s1 + start, len - start + 1);
	return (trimmedstr);
}

// int	main(void)
// {
// 	char const	s1[] = "1234Haben123321";
// 	char const	set[] = "123";
// 	printf("%d\n", getfirst(s1, set));
// 	printf("%d\n", getlast(s1, set));
// 	char *p = ft_strtrim(s1, set);
// 	printf("%s\n", p);
// }
