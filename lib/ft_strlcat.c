/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:22:11 by yoel-idr          #+#    #+#             */
/*   Updated: 2022/10/16 09:45:31 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	l_dest;
	size_t	l_src;
	size_t	index;
	size_t	len;

	l_dest = ft_strlen(dest);
	l_src = ft_strlen(src);
	len = l_dest;
	if (size <= l_dest || size == 0)
		return (l_src + size);
	index = 0;
	while (src[index] && len < size - 1)
		dest[len++] = src[index++];
	dest[len] = '\0';
	return (l_dest + l_src);
}
