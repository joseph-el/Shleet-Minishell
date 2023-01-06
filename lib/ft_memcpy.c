/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:13:20 by yoel-idr          #+#    #+#             */
/*   Updated: 2022/10/15 22:50:02 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
