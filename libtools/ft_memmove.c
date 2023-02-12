/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:21:07 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 01:15:38 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*ptr;
	char	*scn;

	ptr = (char *)dest;
	scn = (char *)src;
	if (scn < ptr)
	{
		while (len-- > 0)
		*(ptr + len) = *(scn + len);
	}
	else
		ft_memcpy(ptr, scn, len);
	return (ptr);
}
