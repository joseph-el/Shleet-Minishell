/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:57:26 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/17 00:10:33 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtools.h"

char    *ft_strndup(char *src, int len)
{
    char    *dest;

    dest = malloc(len + 1);
    if (!dest)
        return (NULL);
    ft_strlcpy(dest, src, len + 1);
    return (dest);
}