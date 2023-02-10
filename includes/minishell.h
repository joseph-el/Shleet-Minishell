/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:43:10 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/10 20:48:05 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <paths.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# include <readline/history.h>
# include <readline/readline.h>

# include "libtools.h"
# include "gc_memory.h"
# include "lexer.h"
# include "environment.h"
# include "expander.h"
# include "executor.h"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"
# define BREAKING 1
# define RUNING 2

typedef struct s_global
{
	t_gc	*gc;
	t_env	*envp;
	int		status;
	int		*fd_io;
}			t_global;

t_global	g_global;

/**
 *  @brief  Global Utils
 */

void 		init_signal(void);
void		print_expander(t_expander *l_expander);
void		print_arr(char **arr);
int 		*io_save(void);
void    	reset_io(int *fds);
void		shleet_error(char *error_msg, char *specify, int status);
void		clean_out(void);
int 		ft_close(int fds[2], int fd_tmp);
int			ft_pipe(int fds[2]);
pid_t		ft_fork(void);
int 		ft_dup2(int fd1, int fd2);
int			shleet_status(void);
bool    	is_builtins(char *arg);
bool 		is_pipe(t_cmdexc *head_grp);

/**
 *  @brief builtins commands
 */

void		shleet_export(char **cmd);
void		shleet_pwd(char **cmd);
void		shleet_echo(char **cmd);
void 		shleet_cd(char **cmd_args);
void		shleet_exit(char **args);
void		shleet_env(char **args);
void		shleet_unset(char **args);

#endif
