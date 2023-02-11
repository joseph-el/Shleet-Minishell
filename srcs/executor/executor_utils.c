/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:24:31 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/11 20:08:40 by yoel-idr         ###   ########.fr       */
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
        else
            right->grb->is_executed = 1;
    }
}

void    run_grb(t_grb *grb)
{
    int     fds[2];
    int     status;
    
    status = 0;
    if (!grb || !grb->head || grb->is_executed)
        return ;
    if (is_pipe(grb->head))
        pipeline(grb->head);
    else
        run_cmdline(grb->head, 0, fds, CMDEXC);
    grb->is_executed = true;
    while (wait(&status) != -1)
        ;
    if (status != 0)
        g_global.status = status;
    reset_io(g_global.fd_io);
}

bool    builtins(t_cmdexc *obj, int fds[2], int fd_tmp, int flag)
{
    if (is_builtins(*obj->cmdexc))
        fd_duplicate(obj, fds, fd_tmp, flag);
    if (!ft_strncmp(*obj->cmdexc, "echo", sizeof("echo") + 1))
        return (shleet_echo(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "exit", sizeof("exit") + 1))
        return (shleet_exit(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "export", sizeof("export") + 1))
        return (shleet_export(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "cd", sizeof("cd") + 1))
        return (shleet_cd(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "unset", sizeof("unset") + 1))
        return (shleet_unset(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "pwd", sizeof("pwd") + 1))
        return (shleet_pwd(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "env", sizeof("env") + 1))
        return (shleet_env(obj->cmdexc + 1), true);
    else
        return (false);
}

void run_cmdline(t_cmdexc *obj, int fd_tmp, int fds[2], int flag)
{
    pid_t   pid;
    
    if (!obj || !obj->cmdexc || builtins(obj, fds, fd_tmp, flag))
        return (reset_io(g_global.fd_io));
    pid = ft_fork();
    if (!pid)
    {
        close(*fds);
        if (fd_duplicate(obj, fds, fd_tmp, flag) < 0)
            exit(1);
        ft_execve(*obj->cmdexc, obj->cmdexc);
        shleet_error(*obj->cmdexc, strerror(errno), 1);
        if (errno == ENOENT)
            exit(127);
        if (errno == EACCES)
            exit(126);
        exit(EXIT_FAILURE);
    }
}