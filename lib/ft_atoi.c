/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:12:22 by yoel-idr          #+#    #+#             */
/*   Updated: 2022/10/17 16:40:11 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_return(unsigned long long number, int sign)
{
	if (number > 9223372036854775807 && sign == 1)
		return (-1);
	if (number > 9223372036854775807 && sign == -1)
		return (0);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long long	number;
	int					sign;
	unsigned long long	x;

	number = 0;
	sign = 1;
	x = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		x = (x * 10) + (*str - '0');
		if (x / 10 != number)
			return (-1);
		number = (number * 10) + (*str - '0');
				str++;
		if ((number > 9223372036854775807 && sign == 1)
			|| (number > 9223372036854775807 && sign == -1))
			return (check_return(number, sign));
	}
	return (number * sign);
}
