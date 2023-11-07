/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zzzzz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:21:32 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/07 20:01:23 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	arr_length(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	compare_first_char(const char *str1, const char *str2)
{
	return (str1[0] - str2[0]);
}

char	**sorted_envi(char **envi)
{
	int		length;
	char	**sorted_envi;
	int		i;
	int		j;
	char	*tmp;

	length = arr_length(envi);
	tmp = NULL;
	sorted_envi = (char **)malloc(sizeof(char *) * (length + 1));
	i = -1;
	j = -1;
	if (!sorted_envi)
		return (NULL);
	while (++i < length)
		sorted_envi[i] = strdup(envi[i]);
	i = -1;
	while (++i < length - 1)
	{
		j = -1;
		while (++j < length - i - 1)
		{
			if (compare_first_char(sorted_envi[j], sorted_envi[j + 1]) > 0)
			{
				tmp = sorted_envi[j];
				sorted_envi[j] = sorted_envi[j + 1];
				sorted_envi[j + 1] = tmp;
			}
		}
	}
    return (sorted_envi);
}

void	print_export(char **envi_arr)
{
	char	**tmp_arr;
	int		i;

	i = -1;
	tmp_arr = sorted_envi(envi_arr);
	while (tmp_arr[++i])
		printf("declare -x %s\n", tmp_arr[i]);
	// ft_clean_arr(tmp_arr);
}

int main(void)
{
	char **arr = malloc(sizeof(char *) * 10);
	arr[0] = strdup("LS_COLORS");
	arr[1] = strdup("PATH");
	arr[2] = strdup("PWD");
	arr[3] = strdup("HOME");
	arr[4] = strdup("OLDPWD");
	arr[5] = strdup("SHLVL");
	arr[6] = strdup("ZSH");
	arr[7] = strdup("TERM");
	arr[8] = strdup("USER");
	arr[9] = NULL;
	print_export(arr);
}
