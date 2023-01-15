/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:02:51 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/14 19:17:11 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
#define GC_H

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_dustbin
{
    void                *address;
    struct s_dustbin    *next; 
}               t_dustbin;

typedef struct s_gc
{
    t_dustbin       *garbage;
    struct  s_gc    *(*gc_adding_address)(struct s_gc *, void *);
    void            *(*gc_filter)(struct s_gc *, void *);
    void            (*gc_clean_dustbin)(t_dustbin **);
}               t_gc;

/*
* @gc__ function
*/

t_gc    *gc_init(void);
t_gc    *gc_adding_adress(t_gc *gc, void *address);
void    *gc_filter(t_gc *gc, void *newaddress);
void    gc_clean_dustbin(t_dustbin **dustbin);
void    exit_status(int status, void *msg);

#endif