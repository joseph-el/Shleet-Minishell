/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:22:32 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:30:57 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (*s1 == *s2 && i < n)
	{
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		s1++;
		s2++;
		i ++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
