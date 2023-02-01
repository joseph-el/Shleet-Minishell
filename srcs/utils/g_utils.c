/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:51:40 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/01 20:30:03 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_close(int fd1, int fd2)
{
    close(fd1);
    close(fd2);
}

pid_t   ft_fork(void)
{
    pid_t   _pid;

    _pid = fork();
    if (_pid == -1)
        shleet_error("fork", "unable to creat a process", 2);
    return (_pid);
}

int ft_pipe(int fds[2])
{
    int ret;

    ret = pipe(fds);
    if (ret == -1)
        shleet_error("pipe", "unable to create a pipe", 2);
    return (ret);
}

void    clean_out(void)
{
    gc_purifying(&g_global.gc, CLEAN_ALL);
    // rl_clear_history();
    exit(EXIT_SUCCESS);
}
