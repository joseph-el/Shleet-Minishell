/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:20:04 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/30 23:46:06 by yoel-idr         ###   ########.fr       */
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

int ft_execve(char *cmd, char **cmd_argument);


#endif