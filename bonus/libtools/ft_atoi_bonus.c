/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:49:13 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:30:08 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools_bonus.h"

static int	sign_check(int sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	tmp;
	long	result;
	int		i;
	int		sign;

	tmp = 0;
	i = 0;
	result = 0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		if (tmp > result)
			return (sign_check(sign));
		tmp = result;
		i++;
	}
	return (result * sign);
}
