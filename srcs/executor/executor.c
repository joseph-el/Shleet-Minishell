/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:50:09 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 00:26:11 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

# define RIGHT_SIDE 1 << 1
# define LEFT_SIDE 1 << 2
# define FD_TMP 1 << 3

pid_t   run_pipe(t_cmdexc *object, int fds[2], int *fd_tmp, int fd_flag)
{
    pid_t   pid;
    int     fd_write;
    int     fd_read;

    /**
     * @brief init io_fd of child process
     */
    if (fd_flag & LEFT_SIDE)
    {
        fd_write = fds[1];
        fd_read = object->io_src;
        if (fd_flag & FD_TMP)
            fd_read = *fd_tmp;
    }
    if (fd_flag & RIGHT_SIDE)
    {
        fd_read = *fd_tmp;
        fd_write = object->io_dest;
        if (fd_flag & FD_TMP)
            fd_write = fds[1];
    }
    pid = fork();
    if (pid == 0)
    {
        dup2(fd_write, 1);
        dup2(fd_read, 0);
        run_cmdline(object->cmdexc[0], object->cmdexc + 1);
    }
    close(*fd_tmp);
    *fd_tmp = dup(fds[0]);
    return (pid);
}

void    pipeline(t_cmdexc *left, t_cmdexc *right, int *fd_tmp)
{
    pid_t   process[2];
    int     fds[2];
    int     status;
    int     fd_flag;
    
    if (left->io_dest == -1 || left->io_src == -1 || right->io_dest == -1 || right->io_src == -1)
            shleet_error("No such file or directory", NULL, 2); // return
    pipe(fds);
    fd_flag = LEFT_SIDE | FD_TMP;
    if (left->prev == NULL)
        fd_flag = LEFT_SIDE;
    process[0] = run_pipe(left, fds, fd_tmp, fd_flag);
    if (process[0] == -1)
        return ;
    fd_flag = RIGHT_SIDE;
    if (right->next && right->next->node_type == NODE_PIPE)
        fd_flag = RIGHT_SIDE | FD_TMP;
    process[1] = run_pipe(right, fds, fd_tmp, fd_flag);
    if (process[1] == -1)
        return ;
    ft_close(fds[0], fds[1]);
    if (wait(&status) == process[0])
        g_global.status = status;
    if (wait(&status) == process[1])
        g_global.status = status;
}

void    run_grb(t_grb *object)
{
    t_cmdexc    *head;
    int         *fd_tmp;

    if (!head)
        return ;
    fd_tmp = gc(g_global.gc, malloc(sizeof(int)), TMP);
    while (head)
    {
        if (head->next && head->next->node_type & NODE_PIPE)
        {
            pipeline(head, head->next->next, fd_tmp);
            head = head->next->next->next;
        }
        else
        {
            run_cmd(head); // creat child process :-)
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
            head = head->next->next->next; // (cmd | cmd * ) ==> goto (*) address
        }
        else if (head->nature & NODE_CMDEXC)
        {
            run_grb(head->grb);
            head = head->next;
        }
    }
    return (EXIT_SUCCESS);
}

