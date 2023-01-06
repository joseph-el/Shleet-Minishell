/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:20:58 by yoel-idr          #+#    #+#             */
/*   Updated: 2022/10/16 00:38:54 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*dd;
	unsigned char	*ss;
	size_t			i;

	i = 0;
	ss = (unsigned char *)s1;
	dd = (unsigned char *)s2;
	while (i < n)
	{
		if ((ss[i] - dd[i]) != 0)
			return (ss[i] - dd[i]);
		i ++;
	}
	return (0);
}
