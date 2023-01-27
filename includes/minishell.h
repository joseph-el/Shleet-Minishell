/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:56:05 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/25 22:05:55 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <paths.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../gc_memory/include/gc_memory.h"
# include "../libtools/libtools.h"

# include "environment.h"
# include "lexer.h"
# include "expander.h"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"


typedef struct s_global
{
    t_gc    *gc;
    t_env   *envp;
    short   status;
}               t_global;

t_global    g_global;


void	shleet_error(char *error_msg, char *specify, int status);


#endif