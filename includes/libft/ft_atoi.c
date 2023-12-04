/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 03:54:06 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 03:54:06 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t' || str[i] == \
		'\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	if ((num * sign) < -2147483648)
		return (0);
	else if ((num * sign) > 2147483647)
		return (-1);
	return ((int) sign * num);
}

// int	main(void)
// {
// 	char	str[] = "		-3457634764572234234354354836hello world";
// 	printf("\n%d\n", ft_atoi(str));
// 	printf("%d\n", atoi(str));
// }
