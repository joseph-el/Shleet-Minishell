/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:23:46 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/06 21:23:26 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HEAD 1

typedef struct s_parce
{
    char    *cmd;
    char    **line;
    int     status;
    
}               t_parce;



#endif