/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:49:57 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/10 13:04:41 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <errno.h>
# include <sys/stat.h>

# define PIPE_LINE 8
# define PROCESS 1
# define CMDEXC 16
# define OUTPUT 2
# define INPUT 4

int		ft_execve(char *cmd, char **cmd_argument);
int		executor(t_expander *l_expander);

bool	builtins(t_cmdexc *obj, int fds[2], int fd_tmp, int flag);
int		fd_duplicate(t_cmdexc *obj, int fds[2], int fd_tmp, int flag);
void	run_cmdline(t_cmdexc *obj, int fd_tmp, int fds[2], int flag);
void	run_logical(t_exp *left, t_exp *right, t_type type);
void	pipeline(t_cmdexc *head);
void	run_grb(t_grb *grb);

#endif