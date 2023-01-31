/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:23:48 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 11:40:07 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int herdoc(char *limiter, int *fds)
{
    char    *line;
    int     limiter_size;

    if (!limiter || pipe(fds) == -1)
        return (-1);
    limiter_size = ft_strlen(limiter);
    while (true)
    {
        line = readline("> ");
        if (!line || !ft_memcmp(limiter, line, limiter_size + 1))
			break ;
        gc_adding_adress(g_global.gc, line, TMP);
        write(fds[WIRITE_], line, ft_strlen(line));
		write(fds[READ_], "\n", 1);
    }
    return (close(fds[WIRITE_]), fds[READ_]);
}

char	**realloc_array(char **array, char *new)
{
	char	**ret;
	int		i;

	i = -1;
	if (!array)
	{
		ret = gc(g_global.gc, malloc(sizeof(char *) * 2), TMP);
		return (ret[0] = gc(g_global.gc, ft_strdup(new), TMP),\
			ret[1] = NULL, ret);
	}
	while (array[++i])
		;
	ret = gc(g_global.gc, malloc(sizeof(char *) * (i + 2)), TMP);
	if (!ret)
		return (NULL);
	i = -1;
	while (array[++i])
		ret[i] = gc(g_global.gc, ft_strdup(array[i]), TMP);
	ret[i++] = gc(g_global.gc, ft_strdup(new), TMP);
	ret[i] = NULL;
	return (ret);
}

void    add_cmdexc_back(t_grb **grb, t_cmdexc *new_cmdexc)
{
    if (!(*grb)->head)
        (*grb)->head = new_cmdexc;
    else
    {
        (*grb)->tail->next = new_cmdexc;
        new_cmdexc->prev = (*grb)->tail;
    }
    (*grb)->tail = new_cmdexc;
}