/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:08 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/08 13:55:05 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
#define TREE_H

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


typedef struct s_data
{
    char **Args;
    int     len;
}               t_data;

typedef struct s_tree 
{  
    char      **data;  
    struct s_tree *left;
    struct s_tree *right;   
}               t_tree;

#endif