/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:33:32 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/30 20:58:23 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
// void	exec_cmd(char *cmd, char **argv)
// {
// 	int	pid;
// 	if (is_builtin(cmd, argv + 1))
// 		return ;
// 	pid = ft_fork();
// 	if (pid == -1)
// 		return ;
// 	else if (pid == 0)
// 	{
// 		term_restore();
// 		ft_execvp(cmd, argv);
// 		_error(cmd, strerror(errno), NULL, 1);
// 		gc_clean(&g_global.gc, GC_DESTROY_SELF);
// 		if (errno == ENOENT)
// 			exit(127);
// 		if (errno == EACCES)
// 			exit(126);
// 		exit(1);
// 	}
// 	waitpid(pid, &g_global.status, WUNTRACED);
// 	check_status();
// }

int ft_execve(char *cmd, char **cmd_argument);

int pipe_size(t_cmdexc *object)
{
    int size;

    size = 0;
    if (!object)
        return (size);
    while (object)
    {
        size += (object->node_type == NODE_PIPE);
        object = object->next;
    }
    return (size);
}

// pid_t	run_pipe(t_cmdexc *cmdline, int fds[2], int side)
// {
// 	pid_t		pid;
// 	int			end;
// 	int			fileno;

// 	end = WIRITE_;
// 	fileno = STDOUT_FILENO;
// 	if (side & READ_)
// 	{
// 		end = READ_;
// 		fileno = STDIN_FILENO;
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		ft_dup2(fds[end], fileno);
// 		close_pipe(fds);
// 		exit(get_status());
// 	}
// 	return (pid);
// }




bool is_builtins(char *args, char **list_args)
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

void    run_logical(t_grb *left, t_grb *right, t_type type)
{
    run_grb(left);
    if (type & NODE_AND)
    {
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) == 0)
            run_grb(right);
    }
    else
    {
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) != 0)
            run_grb(right);
    }
}

# define LEFT_SIDE 1 << 1
# define RIGHT_SIDE 1 << 2
# define FD_TMP 1 << 3


void ft_close(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}

void    run_cmdline(char *cmdline, char  **cmd_argument)
{
    if (is_builtins(cmdline, cmd_argument))
        return ;
    ft_execve(cmdline, cmd_argument);
    shleet_error(cmdline, strerror(errno), 1);
	if (errno == ENOENT)
        exit(127);
    if (errno == EACCES)
		exit(126);
}

void dup_fd(t_cmdexc *object, int fd, int fd2, int mode)
{
    
}

pid_t   run_pipe(t_cmdexc *object, int fds[2], int *fd_tmp, int mode)
{
    pid_t   pid;
    
    if (object->io_dest == -1 || object->io_src == -1)
        return (shleet_error("No such file or directory", NULL, 2), -2);
    
    pid = fork();
    if (pid == 0)
    {
        if (object->io_src > 0)
            dup2(object->io_src, STDIN_FILENO);
        
        dup2(fds[1], STDOUT_FILENO);
        run_cmdline(object->cmdexc[0], object->cmdexc);
    }
    close(*fd_tmp);
    *fd_tmp = dup(fds[0]);
    return (pid);
}


void    pipeline(t_cmdexc *left, t_cmdexc *right, int *fd_tmp)
{
    pid_t       process[2];
    int         fds[2];
    int         status;
    bool        mode;
    static int  rem;

    mode = (right->next && right->next->node_type == NODE_PIPE);
    if (!rem)
        process[0] = run_pipe(left, fds, fd_tmp, LEFT_SIDE);
    else
        process[0] = run_pipe(left, fds, fd_tmp, LEFT_SIDE | FD_TMP);
    if (!mode)
        process[1] = run_pipe(right, fds, fd_tmp, RIGHT_SIDE);
    else
        process[1] = run_pipe(right, fds, fd_tmp, RIGHT_SIDE | FD_TMP);
    
    ft_close(fds);




    // wait two process <<|>>
    if (wait(&status) == process[0])
        g_global.status = status;
    
    if (wait(&status) == process[1])
        g_global.status = status;
}


void    run_grb(t_grb *object)
{
    t_cmdexc    *head;
    int         *fd_tmp;
    bool        mode;
    
    head = object->head;
    fd_tmp = gc(g_global.gc, malloc(sizeof(int)), TMP);
    while (head)
    {
        if (head->next && head->next->node_type & NODE_PIPE)
        {
            // mode = (head->next->next->next && head->next->next->next == NODE_PIPE);
            pipeline(head, head->next->next, fd_tmp);
            head = head->next->next->next;
        }
        else
        {
            run_cmdline(head->cmdexc[0], head->cmdexc);
            head = head->next;
        }
    }
}

// void    run_grb(t_grb *object)
// {
//     t_cmdexc    *head;

//     head = object->head;
//     if (head->next && head->next->node_type & NODE_PIPE)
//         return (pipeline(head, pipe_size(head)));
//     else
//         return (run_cmd());
// }











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
        else if (head->nature & NODE_CMDEXC)
        {
            run_grb(head);
            head = head->next;
        }
    }
    return (EXIT_SUCCESS);
}