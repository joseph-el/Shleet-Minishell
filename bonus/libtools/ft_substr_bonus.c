/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:22:49 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:31:03 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*p;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	p = str;
	s += start;
	while (len-- > 0)
		*str++ = *s++;
	*str = 0;
	return (p);
}
