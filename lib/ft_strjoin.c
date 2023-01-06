/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:22:00 by yoel-idr          #+#    #+#             */
/*   Updated: 2022/10/17 14:23:36 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cpy(char *dest, const char *s1, const char *s2)
{
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		lenght;

	if (!s1 || !s2)
		return (NULL);
	lenght = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (lenght + 1));
	if (!str)
		return (NULL);
	cpy(str, s1, s2);
	return (str);
}
