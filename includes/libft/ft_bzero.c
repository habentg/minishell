/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:54:14 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:54:14 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t n)
{
	ft_memset(dest, 0, n);
}

// int	main(void)
// {
// 	char buf[10];
// 	ft_bzero(buf, 10);
// 	for (int x = 0; x < 10; x++)
// 	{
// 		printf("%d ", buf[x]);
// 	}
// 	printf("%s\n", "done");
// }
