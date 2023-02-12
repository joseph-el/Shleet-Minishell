/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:53:00 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/30 23:55:11 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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

void    run_cmdline(char *cmdline, char  **cmd_argument)
{
    if (is_builtins(cmdline, cmd_argument + 1))
        return ;
    ft_execve(cmdline, cmd_argument + 1);
    shleet_error(cmdline, strerror(errno), 1);
	if (errno == ENOENT)
        exit(127);
    if (errno == EACCES)
		exit(126);
}

bool    is_builtins(char *args, char **list_args)
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

