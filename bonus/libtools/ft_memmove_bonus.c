/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:21:07 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:30:30 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools_bonus.h"

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
