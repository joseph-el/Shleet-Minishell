/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:49:57 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/09 15:59:26 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <errno.h>
# include <sys/stat.h>
        
# define PIPE_LINE 8
# define BUILTINS 64
# define PROCESS 1
# define CMDEXC 16
# define OUTPUT 2
# define INPUT 4

void    run_logical(t_exp *left, t_exp *right, t_type type);

void    run_cmdline(t_cmdexc *obj, int fd_tmp, int fds[2], int flag);
// int    run_cmdline(t_cmdexc *obj, int fd_tmp, int fds[2], int flag);
void    run_cmd(t_cmdexc *cmdline);
void    run_grb(t_grb *grb);
bool    is_pipe(t_cmdexc *head_grp);


void    process(t_cmdexc *obj, int fds[2], int fd_tmp, int flag);
void    pipeline(t_cmdexc *head);
int     fd_duplicate(t_cmdexc *obj, int fds[2], int fd_tmp, int flag);
int     executor(t_expander *l_expander);
int		ft_execve(char *cmd, char **cmd_argument);

// # define RIGHT_SIDE 1 << 0
// # define LEFT_SIDE 1 << 1
// # define FD_TMP 1 << 2

// int		executor(t_expander *l_expander);

// void	run_grb(t_grb *object);
// void	run_cmdline(char *cmdline, char **cmd_argument);
// void	run_logical(t_exp *left, t_exp *right, t_type type);
// void	run_cmd(t_cmdexc *cmdline);
// pid_t   run_pipe(t_cmdexc *obj, int fds[2], int *fd_tmp, int fd_flag);
// void    pipeline(t_cmdexc *left, t_cmdexc *right, int *fd_tmp);
// bool	is_builtins(char *args, char **list_args);

#endif