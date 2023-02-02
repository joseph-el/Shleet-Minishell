/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:38:34 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/02 18:58:24 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t   run_pipe(t_cmdexc *obj, int fds[2], int fd_tmp, int fd_flag)
{
    pid_t   pid;
    int     fd_write;
    int     fd_read;
    
    if (fd_flag & LEFT_SIDE)
    {
        fd_write = fds[1];
        fd_read = obj->io_src;
        if (fd_flag & FD_TMP)
            fd_read = dup(fd_tmp);
    }
    if (fd_flag & RIGHT_SIDE)
    {
        fd_write = obj->io_dest;
        fd_read = fd_tmp;
        if (fd_flag & FD_TMP)
            fd_write = fds[1];
    }
    pid = ft_fork();
    if (pid == 0)
    {
        dup2(fd_write, 1);
        dup2(fd_read, 0);
        run_cmdline(obj->cmdexc[0], obj->cmdexc + 1);
    }
    return (pid);
}

void    pipeline(t_cmdexc *left, t_cmdexc *right, int fd_tmp)
{
    pid_t   process[2];
    int     fds[2];
    int     status;
    int     fd_flag;
    
    fd_flag = LEFT_SIDE | FD_TMP;
    
    if (left->prev == NULL)
        fd_flag = LEFT_SIDE;
        
    process[0] = run_pipe(left, fds, fd_tmp, fd_flag);
    
    fd_flag = RIGHT_SIDE;
    
    if (right->next != NULL)
        fd_flag = RIGHT_SIDE | FD_TMP;
    
    process[1] = run_pipe(right, fds, fd_tmp, fd_flag);

    while (wait(&status) != -1);
    g_global.status = WEXITSTATUS(status);
}


































