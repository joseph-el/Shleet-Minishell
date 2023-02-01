/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:49:57 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/01 11:38:48 by yoel-idr         ###   ########.fr       */
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

int     executor(t_expander *l_expander);
int     ft_execve(char *cmd, char **cmd_argument);

void    run_logical(t_exp *left, t_exp *right, t_type type);
void    run_cmdline(char *cmdline, char  **cmd_argument);
void    run_cmd(t_cmdexc *cmdline);
void    run_grb(t_grb *object);
bool    is_builtins(char *args, char **list_args);

pid_t   run_pipe(t_cmdexc *object, int fds[2], int *fd_tmp, int fd_flag);
void    pipeline(t_cmdexc *left, t_cmdexc *right, int *fd_tmp);

#endif