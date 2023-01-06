/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:19:22 by yoel-idr          #+#    #+#             */
/*   Updated: 2022/10/17 10:11:15 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_double(const char *s1, const char *s2, int len)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	if ((i - 1) == len)
		return (1);
	else
		return (0);
}

static char	*errors(const char *big, const char *little, size_t n)
{
	if (little[0] == '\0')
		return ((char *)big);
	if (n == 0)
		return (NULL);
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	len;
	size_t	index;

	if ((little[0] == '\0') || (n == 0))
		return (errors(big, little, n));
	len = ft_strlen(little) - 1;
	index = 0;
	while (*big)
	{
		if (*big == little[0])
		{
			if (check_double(big, little, len))
			{
				index += len;
				if ((index + 1) <= n)
					return ((char *)big);
			}
		}
		big++;
		index++;
	}
	return (NULL);
}
