/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:54:23 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/16 23:54:36 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools.h"

int	len_calculator(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num_str;
	int		len;
	long	num;

	num = n;
	len = len_calculator(num);
	num_str = malloc (len + 1);
	if (!num_str)
		return (NULL);
	num_str[len--] = '\0';
	if (num == 0)
		num_str[0] = '0';
	if (num < 0)
	{
		num_str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		num_str[len--] = num % 10 + '0';
		num /= 10;
	}
	return (num_str);
}
