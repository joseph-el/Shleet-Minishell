/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:57:26 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:31:00 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools_bonus.h"

char	*ft_strndup(char *src, int len)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, len + 1);
	return (dest);
}
