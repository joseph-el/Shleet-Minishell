/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:20:58 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:30:25 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools_bonus.h"

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
