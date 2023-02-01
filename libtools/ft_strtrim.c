/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:22:39 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/01 16:22:59 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools.h"

char    *ft_strtrim(char const *s1, char const *set)
{
    int        i;
    int        j;

    if (!s1)
        return (NULL);
    i = 0;
    j = ft_strlen(s1) - 1;
    while (ft_strchr(set, s1[i]) && s1[i])
        i++;
    if (s1[i] == '\0')
        return (ft_strdup(""));
    while (ft_strchr(set, s1[j]) && j)
        j--;
    return (ft_substr(s1, i, j - i + 1));
}