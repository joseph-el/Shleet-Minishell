/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:49:57 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/02 19:32:03 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <errno.h>
# include <sys/stat.h>

# define RIGHT_SIDE 1 << 0
# define LEFT_SIDE 1 << 1
# define FD_TMP 1 << 2

int		executor(t_expander *l_expander);
int		ft_execve(char *cmd, char **cmd_argument);

void	run_grb(t_grb *object);
void	run_cmdline(char *cmdline, char **cmd_argument);
void	run_logical(t_exp *left, t_exp *right, t_type type);
void	run_cmd(t_cmdexc *cmdline);
pid_t   run_pipe(t_cmdexc *obj, int fds[2], int *fd_tmp, int fd_flag);
void    pipeline(t_cmdexc *left, t_cmdexc *right, int *fd_tmp);
bool	is_builtins(char *args, char **list_args);

#endif