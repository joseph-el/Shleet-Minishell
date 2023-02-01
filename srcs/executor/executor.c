/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:59:17 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/01 12:23:38 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define RIGHT_SIDE 1 << 1
# define LEFT_SIDE 1 << 2
# define FD_TMP 1 << 3

        /* fork return <pipeline> */
    /*
    *    if (process[1] == -1)
    *        return ;
    *    if (process[0] == -1)
    *        return ;
        */

pid_t   run_pipe(t_cmdexc *object, int fds[2], int *fd_tmp, int fd_flag)
{
    pid_t   pid;
    int     fd_write;
    int     fd_read;
    
    if (fd_flag & LEFT_SIDE)
    {
        fd_write = fds[1];
        fd_read = object->io_src;
        if (fd_flag & FD_TMP)
            fd_read = *fd_tmp;
    }

    if (fd_flag & RIGHT_SIDE)
    {
        fd_write = object->io_dest;
        fd_read = *fd_tmp;
        if (fd_flag & FD_TMP)
            fd_write = fds[1];
    }
    
    pid = ft_fork();
    if (pid == 0)
    {
        dup2(fd_write, 1);
        dup2(fd_read, 0);
        run_cmdline(object->cmdexc[0], object->cmdexc + 1);
    }
    (*fd_tmp) = dup(*fds);
    return (pid);
}

void    pipeline(t_cmdexc *left, t_cmdexc *right, int *fd_tmp)
{
    pid_t   process[2];
    int     fds[2];
    // int     status;
    int     fd_flag;
    
    ft_pipe(fds);
    
    fd_flag = LEFT_SIDE | FD_TMP; // set flag for read from fd_tmp;
    if (left->prev == NULL)
        fd_flag = LEFT_SIDE;      // read from first_cmd->io_src;
    
    
    process[0] = run_pipe(left, fds, fd_tmp, fd_flag);
    
    
    fd_flag = RIGHT_SIDE; // write in last_cmd->io_dest;
    if (right->next && right->next->node_type == NODE_PIPE)
        fd_flag = RIGHT_SIDE | FD_TMP; // write in fd_tmp;
    
    
    process[1] = run_pipe(right, fds, fd_tmp, fd_flag);

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