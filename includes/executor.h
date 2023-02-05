/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:10:59 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/03 14:17:16 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/stat.h>
# include <errno.h>
# include "minishell.h"

/* Execution utils */
int		ft_execve(char *cmd, char **cmd_argument);
int		pipes_counter(t_cmdexc *head_grp);
void	logical_manager(t_exp *logical_node);
void	group_manager(t_cmdexc *head_grp);
bool    is_builtins(char *args, char **list_args);
void	exec_pipline(t_cmdexc *head_grp);
int		exec_cmd(t_cmdexc *cmd_data);
int	    exec_cmdline(char *cmd, char **cmd_args);
int		executor(t_expander *exp_list);

#endif