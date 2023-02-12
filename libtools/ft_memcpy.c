/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:13:20 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 01:15:38 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*p;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	p = dest;
	i = 0;
	while (i < n)
	{
		*(char *)dest++ = *(char *)src++;
		i ++;
	}
	return (p);
}
