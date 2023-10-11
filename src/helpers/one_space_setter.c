/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_space_setter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:25:50 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/11 21:29:27 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'\
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	ft_whitespaces(char *str, int *index, char c)
{
	int	i;

	i = *index;
	if (c == 'f')
	{
		while (str[++i])
		{
			if (!is_whitespace(str[i]))
				break ;
		}
	}
	else if (c == 'b')
	{
		while (--i >= 0)
		{
			if (!is_whitespace(str[i]))
				break ;
		}	
	}
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*sett(char *str, char *res, int start, int end)
{
	int	i;

	i = -1;
	while (start <= (end + 1))
	{
		if (is_whitespace(str[start]))
		{
			res[++i] = ' ';
			start = ft_whitespaces(str, &start, 'f');
		}
		else if (is_operator(str[start]))
		{
			if (start != 0)
				res[++i] = ' ';
			if (is_heredoc(str, start) || is_append(str, start))
			res[++i] = str[start];
			res[++i] = ' ';
			start = ft_whitespaces(str, &start, 'f');
		}
		else
			res[++i] = str[start++];
	}
	res[i] = '\0';
	return (res);
}

char	*one_space_setter(char *str)
{
	int		i;
	int		start;
	int		end;
	int		str_size;
	char	*res;

	i = -1;
	str_size = (int)ft_strlen(str);
	start = ft_whitespaces(str, &i, 'f');
	end = ft_whitespaces(str, &str_size, 'b');
	res = NULL;
	if (!str)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	return (sett(str, res, start, end));
}

int	main(void)
{
	printf("%s\n", one_space_setter(">> a.txt |habe k   haben>        f"));
}
