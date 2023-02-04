/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:24:31 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/04 21:40:33 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    run_logical(t_exp *left, t_exp *right, t_type type)
{
    run_grb(left->grb);
    if (type & NODE_AND)
    {
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) == 0)
            run_grb(right->grb);
    }
    else
    {
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) != 0)
            run_grb(right->grb);
    }
}

void    run_grb(t_grb *grb)
{
    int fds[2]; // fix seg 
    
    if (!grb || !grb->head || grb->is_executed)
        return ;
    if (is_pipe(grb->head))
        pipeline(grb->head);
    else
        run_cmdline(grb->head, 0, fds, CMDEXC); // fix seg in executor : 24
    grb->is_executed = true;
}

bool    is_builtins(char *cmd, char **cmd_list)
{
    (void)cmd_list;
    if (!ft_strcmp(cmd, "echo"))
        return (true);
    else if (!ft_strcmp(cmd, "exit"))
        return (true);
    else if (!ft_strcmp(cmd, "export"))
        return (true);
    else if (!ft_strcmp(cmd, "cd"))
        return (true);
    else if (!ft_strcmp(cmd, "unset"))
        return (true);
    else if (!ft_strcmp(cmd, "pwd"))
        return (true);
    else if (!ft_strcmp(cmd, "env"))
        return (true);
    else
        return (false);
}

void run_cmdline(t_cmdexc *obj, int fd_tmp, int fds[2], int flag)
{
    pid_t   pid;

    if (!obj || !obj->cmdexc || is_builtins(obj->cmdexc[0], obj->cmdexc))
        return ;
    pid = ft_fork();
    if (pid == 0)
    {
        if (flag & (PIPE | INPUT | OUTPUT | PROCESS))
            if (fd_duplicate(obj, fds, fd_tmp, flag) < 0)
                exit(1);
        if (flag & CMDEXC)
            if (fd_duplicate(obj, fds, fd_tmp, flag) < 0)
                exit(1);
        ft_execve(obj->cmdexc[0], obj->cmdexc);
        shleet_error(obj->cmdexc[0], strerror(errno), 1);
        if (errno == ENOENT)
            exit(127);
        if (errno == EACCES)
            exit(126);
        exit(EXIT_FAILURE);
    }
    if (flag & (INPUT | PROCESS | OUTPUT))
        return (close(fd_tmp), (void)(fd_tmp = dup(fds[0])));
}

bool is_pipe(t_cmdexc *head_grp)
{
    if (!head_grp)
        return (false);
    while (head_grp)
    {
        if (head_grp->node_type == NODE_PIPE)
            return (true);
        head_grp = head_grp->next;
    }
    return (false);
}


