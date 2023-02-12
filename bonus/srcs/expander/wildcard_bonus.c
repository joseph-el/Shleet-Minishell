/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:00:38 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:48:58 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

bool	match(char *text, char *pattern)
{
	if (!*text && !*pattern)
		return (true);
	if (*pattern == '*')
		return (match(text, pattern + 1) || (*text != 0 && match(text + 1,
					pattern)));
	if (*text == *pattern)
		return (match(text + 1, pattern + 1));
	return (false);
}

t_node	*wildcard(t_node *target)
{
	struct dirent	*element;
	DIR				*folder;
	char			*ret;

	folder = opendir(".");
	element = readdir(folder);
	ret = "";
	while (element)
	{
		if (match(element->d_name, target->data))
			ret = gc(g_global.gc, ft_strjoin(gc(g_global.gc, ft_strjoin(ret,
								element->d_name), TMP), " "), TMP);
		element = readdir(folder);
	}
	closedir(folder);
	if (*ret)
		return (target->data = ret, target);
	else
		target->tok = WORD;
	return (target);
}
