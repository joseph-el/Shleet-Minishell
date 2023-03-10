/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:43:10 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/14 10:26:39 by yoel-idr         ###   ########.fr       */
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
# include "gc_memory.h"
# include "libtools.h"
# include "environment.h"
# include "lexer.h"
# include "expander.h"
# include "executor.h"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"

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

void		shleet_error(char *error_msg, char *specify, int status);
int			shleet_status(void);
void		init_signal(void);
void		clean_out(void);
bool		is_builtins(char *arg);
bool		is_pipe(t_cmdexc *head_grp);
int			*io_save(void);
void		reset_io(int *fds);
int			ft_close(int fds[2], int fd_tmp);
int			ft_pipe(int fds[2]);
pid_t		ft_fork(void);
int			ft_dup2(int fd1, int fd2);
void		interrput_handler(int sig);
/**
 *  @brief builtins commands
 */

void		shleet_cd(char **cmd_args);
void		shleet_export(char **cmd);
void		shleet_unset(char **args);
void		shleet_exit(char **args);
void		shleet_echo(char **cmd);
void		shleet_env(char **args);
void		shleet_pwd(char **cmd);

/**
 *  @brief builtins commands utils
 */

int			key_isvalid(char *_env);

#endif
