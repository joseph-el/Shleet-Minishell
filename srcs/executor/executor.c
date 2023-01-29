/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:52:38 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/28 22:06:10 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    run_logical(t_grb *left, t_grb *right, t_type type)
{
    executor(left, type, E_LOGICAL);
    if (type & NODE_AND)
    {
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) == 0)
            executor(right, type, E_LOGICAL);
    }
    else
    {
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) != 0)
            executor(right, type, E_LOGICAL);
    }
}


void    run_grb(t_grb *object)
{
    t_cmdexc *head;

    head = object->head;
    while (head)
    {
        if (    )
    }
}

bool is_builtins(char *args)
{
    /**
     * @brief checking for builtins
     * @return run an builtins 
     */
    if (ft_memcmp(args, "echo", sizeof("echo") + 1))
        return (true); // shleet_echo
    else if (ft_memcmp(args, "cd", sizeof("cd") + 1))
        return (true); //shleet_cd
    else if (ft_memcmp(args, "export", sizeof("export") + 1))
        return (true); //shleet_export
    else if (ft_memcmp(args, "env", sizeof("env") + 1))
        return (true); //shleet_env
    else if (ft_memcmp(args, "unset", sizeof("unset") + 1))
        return (true); //shleet_unset
    else if (ft_memcmp(args, "exit", sizeof("exit") + 1))
        return (true); //shleet_exit
    else if (ft_memcmp(args, "pwd", sizeof("pwd") + 1))
        return (true); //shleet_pwd
    return (false);
}

void    run_pipe(char *cmd, int *io_src, int *io_dest)
{
    
}

// int executor(t_grb *for_execute, t_grb *secondly, t_type logical, exc_flag flag)
// {
//     short status;

//     if (!for_execute)
//         return (EXIT_FAILURE);
//     if (flag == E_GRB)
//         return (run_grb(for_execute), EXIT_SUCCESS);
//     else if (flag == E_PIPE)
//         return (run_pipes(for_execute), EXIT_SUCCESS);
//     else if (flag == E_LOGICAL)
//         return (run_logical(for_execute, secondly, logical), EXIT_SUCCESS);
//     else if (flag == E_CMD)
//         return (run_cmd(for_execute), EXIT_SUCCESS);
//     return (EXIT_SUCCESS);
// }