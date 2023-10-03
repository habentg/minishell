/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:59:21 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:59:21 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int alpha)
{
	if ((alpha >= 32 && alpha <= 126))
		return (1);
	return (0);
}

// int	main(void)
// {
// 	printf("%d", ft_isprint(31));
// }
