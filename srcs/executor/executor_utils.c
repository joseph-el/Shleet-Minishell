/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:53:00 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 17:35:07 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void    run_grb(t_grb *object)
{
    t_cmdexc    *head;
    int         *fd_tmp;

    if (!object)
        return ;
    fd_tmp = gc(g_global.gc, malloc(sizeof(int)), TMP);
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
            if (head->io_dest == -1 || head->io_src == -1)
                return (shleet_error(strerror(ENOENT), NULL, 2));
            run_cmd(head); 
            head = head->next;
        }
    }
}

void    run_cmd(t_cmdexc *cmdline)
{
    pid_t   process;
    int     status;
    
    process = ft_fork();
    if (process == 0)
    {
        dup2(cmdline->io_dest, 1);
        dup2(cmdline->io_src, 0);
        run_cmdline(cmdline->cmdexc[0], cmdline->cmdexc);
    }
    if (process == -1)
        return ;
    if (wait(&status) == process)
        g_global.status = status;
}

void    run_cmdline(char *cmdline, char  **cmd_argument)
{
    // if (is_builtins(cmdline, cmd_argument + 1))
    //     return ;
    fprintf(stderr, "Here ==> |%s|\n", cmdline);
    ft_execve(cmdline, cmd_argument);
    shleet_error(cmdline, strerror(errno), 1);
	if (errno == ENOENT)
        exit(127);
    if (errno == EACCES)
		exit(126);
    exit(EXIT_FAILURE);
}

bool    is_builtins(char *args, char **list_args)
{
    if (!ft_strncmp(args, "echo", ft_strlen("echo")))
        return (shleet_echo(list_args), true);
    
    else if (!ft_strncmp(args, "cd", ft_strlen("cd") + 1))
        return (fprintf(stderr, "Iam here\n"), shleet_cd(list_args, g_global.envp), true);
    
    else if (!ft_strncmp(args, "export", ft_strlen("export")))
        return (shleet_export(list_args, &g_global.envp), true);
    
    else if (!ft_strncmp(args, "env", ft_strlen("env")))
        return (shleet_env(list_args, g_global.envp), true);
    
    else if (!ft_strncmp(args, "unset", ft_strlen("unset")))
        return (shleet_unset(&g_global.envp, list_args), true);
    
    else if (!ft_strncmp(args, "exit", ft_strlen("exit")))
        return (shleet_exit(list_args), true); 
    
    else if (!ft_strncmp(args, "pwd", ft_strlen("pwd")))
        return (shleet_pwd(list_args), true);

    return (false);
}
