/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:59:32 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:59:32 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int alpha)
{
	if ((alpha >= 0 && alpha < 128))
		return (1);
	return (0);
}

// int	main(void)
// {
// 	printf("%d", ft_isascii('1'));
// }
