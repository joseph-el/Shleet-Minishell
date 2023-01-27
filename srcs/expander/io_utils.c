/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:43:32 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/27 18:42:50 by yoel-idr         ###   ########.fr       */
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
    return (close(fds[WIRITE_]), close(fds[READ_]), EXIT_SUCCESS);
}