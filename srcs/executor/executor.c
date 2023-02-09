/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:23:18 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/09 13:49:33 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int fd_duplicate(t_cmdexc *obj, int fds[2], int fd_tmp, int flag)
{
    int fd_write;
    int fd_read;

    if (obj->io_dest == -1 || obj->io_src == -1)
        return (shleet_error("No such file or directory", NULL, 1), -1);
    fd_read = obj->io_src;
    fd_write = fds[1];
    if (flag & PROCESS)
    {
        fd_read = fd_tmp;
        if (obj->io_src != STDIN_FILENO)
            fd_read = obj->io_src;
        if (obj->io_dest != STDOUT_FILENO)
            fd_write = obj->io_dest;
    }
    if (flag & (OUTPUT | CMDEXC))
    {
        fd_read = fd_tmp;
        if (obj->io_src != STDIN_FILENO || flag & CMDEXC)
            fd_read = obj->io_src;
        fd_write = obj->io_dest;
    }
    return (ft_dup2(fd_write, 1) * ft_dup2(fd_read, 0));
}

void    pipeline(t_cmdexc *head)
{
    int fd_tmp;
    int fds[2];

    fd_tmp = 0;
    while (head)
    {
        if (head->node_type & NODE_PIPE)
        {
            head = head->next;
            continue;
        }
        ft_pipe(fds);
        if (!head->prev)
            run_cmdline(head, fd_tmp, fds, PIPE_LINE | INPUT);
        else if (!head->next)
            run_cmdline(head, fd_tmp, fds, PIPE_LINE | OUTPUT);
        else
            run_cmdline(head, fd_tmp, fds, PIPE_LINE | PROCESS);
        ft_close(fds[0], fds[1]);
        head = head->next;
    }
    close(fd_tmp);
}

int     executor(t_expander *l_expander)
{
    t_exp   *head;

    if (!l_expander)
        return (EXIT_FAILURE);
    head = l_expander->head;
    while (head)
    {
        if (head->next && head->next->nature & (NODE_AND | NODE_OR))
        {
            run_logical(head, head->next->next, head->next->nature);
            head = head->next->next;
        }
        else if (head && head->nature & NODE_CMDEXC)
        {
            run_grb(head->grb);
            head = head->next;
        }
    }
    return (EXIT_SUCCESS);
}