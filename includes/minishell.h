/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:50:45 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/17 00:46:16 by yoel-idr         ###   ########.fr       */
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

#include "../libgc/include/gc.h"
#include "../libtools/libtools.h"

#include "lexer.h"

typedef struct s_global
{
    t_gc    *gc;
    char    *prgrame_name;
    short   status;
}               t_global;

extern t_global g_global;









/*----------management_list---------------*/

t_lexer *new_lexer(void);

t_node *creat_node(char *data, t_token token);

t_node  *get_node(t_node *crr_node, int mode);

void    push_back(t_lexer **lexer, t_node *n_node);

void    print_lexer(t_node *node); //debug

/*--------------------------------------*/

#endif
