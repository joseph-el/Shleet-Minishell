/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:13:20 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:30:27 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools_bonus.h"

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
