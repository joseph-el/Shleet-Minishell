/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:58:05 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/02 23:27:03 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t   run_pipe(t_cmdexc *obj, int fds[2], int *fd_tmp, int fd_flag)
{
    pid_t   pid;
    int     fd_write;
    int     fd_read;

    if (fd_flag & LEFT_SIDE)
    {
        fd_write = fds[1];
        fd_read = obj->io_src;
        if (fd_flag & FD_TMP)
            fd_read = *fd_tmp;
    }
    
    if (fd_flag & RIGHT_SIDE)
    {
        fd_write = obj->io_dest;
        fd_read = *fd_tmp;
        if (fd_flag & FD_TMP)
            fd_write = fds[1];
    }
    
    pid = ft_fork();
    if (pid == 0)
    {
        dup2(fd_write, 0);
        dup2(fd_read, 1);
        run_cmdline(obj->cmdexc[0], obj->cmdexc + 1);
    }
    char *test = get_next_line(fds[0]);
    fprintf(stderr, "The content of fds[0] = |%s|\n", test);
    return (pid);
}

void    pipeline(t_cmdexc *left, t_cmdexc *right, int *fd_tmp)
{
    pid_t   process[2];
    int     fds[2];
    int     status;
    int     fd_flag;

    pipe(fds);
    
    fd_flag = LEFT_SIDE | FD_TMP;
    if (left->prev == NULL)
        fd_flag = LEFT_SIDE;
    
    process[0] = run_pipe(left, fds, fd_tmp, fd_flag);
    
    fd_flag = RIGHT_SIDE;
    if (right->next != NULL)
        fd_flag = RIGHT_SIDE | FD_TMP;
    
    process[1] = run_pipe(right, fds, fd_tmp, fd_flag);
    
    close(fds[0]);
    close(fds[1]);
    
    while (wait(&status) != -1);
    g_global.status = WEXITSTATUS(status);
}

int     executor(t_expander *l_expander)
{
    t_exp   *head;

    if (!l_expander)
        return (EXIT_FAILURE);
    head = l_expander->head;
    while (head && head->nature != NODE_ENDOFCMD)
    {
        if (head->next && head->next->nature & (NODE_AND | NODE_OR))
        {
            run_logical(head, head->next->next, head->next->nature);
            head = head->next->next->next;
        }
        if (head && head->nature & NODE_CMDEXC)
        {
            run_grb(head->grb);
            head = head->next;
        }
    }
    fprintf(stderr, "FINISH Goood bye\n");
    return (EXIT_SUCCESS);
}