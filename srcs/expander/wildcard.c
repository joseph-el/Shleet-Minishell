/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:10:32 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/27 20:00:07 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool match(char *text, char *pattern)
{
    if (!*text && !*pattern)
        return (true);
    if (*pattern == '*')
        return (match(text, pattern + 1) || (*text != 0 && match(text + 1, pattern)));
    if (*text == *pattern)
        return match(text + 1, pattern + 1);
    return (false);
}

t_node  *wildcard(t_node *target)
{
    struct 	dirent	*element;
    DIR             *folder;
    char            *ret;
    
	folder = opendir(".");
	element = readdir(folder);
    ret = "";
    while (element)
    {
        if (match(element->d_name, target->data))
            ret = gc(g_global.gc, ft_strjoin(gc(g_global.gc, ft_strjoin(ret, element->d_name), TMP), " "), TMP);
        element = readdir(folder);
    }
    if (ret)
        return (target->data = ret, target);
    else
        target->tok = WORD;
    return (target);
}