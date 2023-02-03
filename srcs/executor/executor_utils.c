/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:24:31 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/03 22:44:16 by yoel-idr         ###   ########.fr       */
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

void    run_cmd(t_cmdexc *cmdline)
{
    pid_t   process;
    int     status;
    
    process = ft_fork();
    if (process == 0)
    {
        ft_dup2(cmdline->io_dest, 1);
        ft_dup2(cmdline->io_src, 0);
        run_cmdline(cmdline->cmdexc);
    }
    if (process == -1)
        return ;
    if (wait(&status) == process)
        g_global.status = WEXITSTATUS(status);
}

void    run_grb(t_grb *grb)
{
    if (!grb || !grb->head || grb->is_executed)
        return ;
    if (is_pipe(grb->head))
    {
        pipeline(grb->head);
    }
    else
        run_cmd(grb->head);
    grb->is_executed = true;
}

void    run_cmdline(char **cmdline)
{
    if (!cmdline)
        return ;
    // fprintf(stderr, "Hey IAM in run_cmd\n");
    ft_execve(cmdline[0], cmdline);
    shleet_error(cmdline[0], strerror(errno), 1);
	if (errno == ENOENT)
        exit(127);
    if (errno == EACCES)
		exit(126);
    exit(EXIT_FAILURE);
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


