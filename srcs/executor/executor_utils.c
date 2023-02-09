/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:24:31 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/09 13:52:07 by yoel-idr         ###   ########.fr       */
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
        right->grb->is_executed = true;
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) != 0)
            run_grb(right->grb);
    }
}

void    run_grb(t_grb *grb)
{
    int     status;
    int     fds[2]; // fix seg 
    
    if (!grb || !grb->head || grb->is_executed)
        return ;
    if (is_pipe(grb->head))
        pipeline(grb->head);
    else
        run_cmdline(grb->head, 0, fds, CMDEXC); // fix seg in executor : 24
    grb->is_executed = true;
    while (wait(&status) != -1)
        ;
    g_global.status = WEXITSTATUS(status);
    reset_io(g_global.fd_io);
}

bool    is_builtins(char *arg)
{
    int len;

    len = ft_strlen(arg);
    if 
    (
        !ft_strncmp(arg, "echo", len) || 
        !ft_strncmp(arg, "exit", len) ||
        !ft_strncmp(arg, "pwd", len) ||
        !ft_strncmp(arg, "unset", len) ||
        !ft_strncmp(arg, "cd", len) ||
        !ft_strncmp(arg, "env", len) ||
        !ft_strncmp(arg, "export", len)
    )
        return (true);
    return (false);
}

bool    builtins(t_cmdexc *obj, int fds[2], int fd_tmp, int flag)
{
    if (flag & PIPE_LINE && is_builtins(*obj->cmdexc))
        fd_duplicate(obj, fds, fd_tmp, flag);

        
    if (!ft_strncmp(*obj->cmdexc, "echo", ft_strlen("echo")))
        return (shleet_echo(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "exit", ft_strlen("exit")))
        return (shleet_exit(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "export", ft_strlen("export")))
        return (shleet_export(obj->cmdexc + 1, &g_global.envp), true);
    else if (!ft_strncmp(*obj->cmdexc, "cd", ft_strlen("cd")))
        return (shleet_cd(obj->cmdexc + 1, g_global.envp), true);
    else if (!ft_strncmp(*obj->cmdexc, "unset", ft_strlen("unset")))
        return (shleet_unset(&g_global.envp, obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "pwd", ft_strlen("pwd")))
        return (shleet_pwd(obj->cmdexc + 1), true);
    else if (!ft_strncmp(*obj->cmdexc, "env", ft_strlen("env")))
        return (shleet_env(obj->cmdexc + 1, g_global.envp), true);
    else
        return (false);
}

void run_cmdline(t_cmdexc *obj, int fd_tmp, int fds[2], int flag)
{
    pid_t   pid;
    
    if (!obj || builtins(obj, fds, fd_tmp, flag))
        return;
    pid = ft_fork();
    if (pid == 0)
    {
        if (flag & (PIPE_LINE | INPUT | OUTPUT | PROCESS))
            if (fd_duplicate(obj, fds, fd_tmp, flag) < 0)
                exit(1);
        if (flag & CMDEXC)
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


