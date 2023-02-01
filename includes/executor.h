/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:49:57 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/01 21:49:03 by yoel-idr         ###   ########.fr       */
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

void    run_grb(t_grb *object);
void    run_cmdline(char *cmdline, char  **cmd_argument);
void    run_logical(t_exp *left, t_exp *right, t_type type);
void    run_cmd(t_cmdexc *cmdline);

bool    is_builtins(char *args, char **list_args);

#endif