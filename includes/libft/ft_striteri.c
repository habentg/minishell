/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:57:11 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:57:13 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	count;
	size_t	x;
	char	*temp;

	if (!s)
		return ;
	temp = (char *)s;
	count = 0;
	x = ft_strlen(s);
	while (count < x)
	{
		f(count, &temp[count]);
		count++;
	}
}
