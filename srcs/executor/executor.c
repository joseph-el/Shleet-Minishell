/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:38:34 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/01 21:50:21 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define RIGHT_SIDE 1 << 1
# define LEFT_SIDE 1 << 2
# define FD_TMP 1 << 3


pid_t   run_pipe(t_cmdexc *obj, int fds[2], int fd_tmp, int fd_flag)
{
    pid_t   pid;
    int     fd_write;
    int     fd_read;
    
    if (fd_flag & LEFT_SIDE)
    {
        fd_write = dup(fds[1]);
        fd_read = dup(obj->io_src);
        if (fd_flag & FD_TMP)
        {
            close(fd_read);
            fd_read = dup(fd_tmp);
        }
    }

    if (fd_flag & RIGHT_SIDE)
    {
        fd_write = dup(obj->io_dest);
        fd_read = dup(fd_tmp);
        if (fd_flag & FD_TMP)
        {
            close(fd_write);
            fd_write = dup(fds[1]);
        }
    }
    
    pid = ft_fork();
    
    if (pid == 0)
    {
        dup2(fd_write, 1);
        dup2(fd_read, 0);
        run_cmdline(obj->cmdexc[0], obj->cmdexc + 1);
    }
    close(fd_tmp);
    fd_tmp = dup(fds[0]);
    
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
    if (right->next && right->next->node_type == NODE_PIPE)
        fd_flag = RIGHT_SIDE | FD_TMP;
    
    process[0] = run_pipe(right, fds, fd_tmp, fd_flag);
    
    while (wait(&status) != -1)
            ;
    g_global.status = WEXITSTATUS(status);
    // if (wait(&status) == process[0])
    //     g_global.status = WEXITSTATUS(status);
    // if (wait(&status) == process[1])
    //     g_global.status = WEXITSTATUS(status);
}













void    run_grb(t_grb *object)
{
    t_cmdexc    *head;
    int         fd_tmp = 0;
    
    if (!object)
        return ;
    head = object->head;
    while (head)
    {
        if (head->next && head->next->node_type == NODE_PIPE)
        {
            pipeline(head, head->next->next, fd_tmp);
            head = head->next->next->next;
        }
        else
        {
            run_cmd(head);
            head = head->next;
        }
    }
}

int executor(t_expander *l_expander)
{
    t_exp   *head;

    head = l_expander->head;
    if (!head || head->nature & NODE_ENDOFCMD)
        return (EXIT_FAILURE);
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
    return (EXIT_SUCCESS);
}