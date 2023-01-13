/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:04:14 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/13 23:17:20 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GC_H
# define GC_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>

#define ALL 0x1
#define TMP 0x2

typedef struct s_list
{
    void        *adress;
    struct s_list *next;
}               t_dustbin;

typedef struct s_gc
{
    t_dustbin   *garbage;
    struct s_gc *(*adding)(struct s_gc *, void *);
    void        (*clean_dustbin)(t_dustbin **);
}               t_gc;

typedef struct s_global
{
    t_gc    *gc;
    char    *program_name;
    short   status;
    bool    is_running;
}               t_global;

extern t_global	g_global;

#endif
