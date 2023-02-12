/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:21:44 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:30:47 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools_bonus.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len + 1);
	return (dest);
}
