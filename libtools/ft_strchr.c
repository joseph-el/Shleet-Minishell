/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:21:39 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/24 19:03:02 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools.h"

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str && *str != (char)c)
		str++;
	if (*str == '\0' && *str != (char)c)
		return (NULL);
	return ((char *)str);
}
