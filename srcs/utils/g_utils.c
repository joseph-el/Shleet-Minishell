/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:51:40 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/09 22:25:49 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_close(int fds[2], int fd_tmp)
{
    int ret;

    close(fd_tmp);
    ret = dup(fds[0]);
    close(fds[WIRITE_]);
    close(fds[READ_]);
    return (ret);
}

pid_t   ft_fork(void)
{
    pid_t   _pid;

    _pid = fork();
    if (_pid < 0)
    {
        shleet_error("fork", "unable to creat a process", 1);
        return (-1);
    }
    return (_pid);
}

int ft_dup2(int fd1, int fd2)
{
    int ret;
    
    ret = dup2(fd1, fd2);
    if (ret < 0)
    {
        shleet_error("dup2", "unable to duplicate", 1);
        return (-1);
    }
    return (2);
}

int ft_pipe(int fds[2])
{
    int ret;

    ret = pipe(fds);
    if (ret < 0)
    {
        shleet_error("pipe", "unable to create a pipe", 1);
        return (-1);
    }
    return (ret);
}

void    clean_out(void)
{
    gc_purifying(&g_global.gc, CLEAN_ALL);
    rl_clear_history();
    exit(EXIT_SUCCESS);
}
