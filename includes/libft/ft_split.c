/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:57:28 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 21:44:09 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	split_writter(char **res, char const *str, char c)
{
	char const	*temp_str;

	temp_str = str;
	while (*temp_str)
	{
		while (*str == c)
			str++;
		temp_str = str;
		while (*temp_str && *temp_str != c)
			temp_str++;
		if (*temp_str == c || temp_str > str)
		{
			*res = ft_substr(str, 0, (temp_str - str));
			str = temp_str;
			res++;
		}
	}
	*res = NULL;
}

int	splited_count(char const *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	size_t	res_size;

	if (!str)
		return (NULL);
	res_size = splited_count(str, c);
	res = (char **)malloc(sizeof(char *) * (res_size + 1));
	if (!res)
		return (NULL);
	split_writter(res, str, c);
	return (res);
}

// int main(void)
// {
//     // char    str[] = NULL;
//     char    c = 'A';

// 	size_t count  =  splited_count(NULL, c);
//     printf("%zu substrings.\n", count);
//     char **arr;

//     arr = ft_split(NULL, c);
//     for(size_t i = 0; i < count + 10; i++)
//     {
//         printf("%s\n", arr[i]);
//     }
// }
