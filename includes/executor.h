/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:20:04 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 16:20:53 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/stat.h>
# include <errno.h>
# include "minishell.h"

# define E_GRB 0x1
# define E_CMD 0x2
# define E_PIPE 0x3
# define E_LOGICAL 0x4

typedef int exc_flag;

pid_t   run_pipe(t_cmdexc *object, int fds[2], int *fd_tmp, int fd_flag);
void    run_logical(t_exp *left, t_exp *right, t_type type);
void    run_cmdline(char *cmdline, char  **cmd_argument);
bool    is_builtins(char *args, char **list_args);
int     ft_execve(char *cmd, char **cmd_argument);
void    run_cmd(t_cmdexc *cmdline);
void    run_grb(t_grb *object);

pid_t   run_pipe(t_cmdexc *object, int fds[2], int *fd_tmp, int fd_flag);
void    pipeline(t_cmdexc *left, t_cmdexc *right, int *fd_tmp);




void    print_expander(t_expander *l_expander);
void    print_arr(char **arr);

#endif