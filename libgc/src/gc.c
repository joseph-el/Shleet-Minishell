/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:22:20 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/14 19:16:12 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/gc.h"

t_gc    *gc_init(void)
{
    t_gc    *gc;

    gc = malloc(sizeof(t_gc));
    if (!gc)
        return (NULL);
    gc->garbage = NULL;
    gc->gc_filter = &gc_filter;
    gc->gc_adding_address = &gc_adding_adress;
    gc->gc_clean_dustbin = &gc_clean_dustbin;
    return (gc);
}

void    exit_status(int status, void *msg)
{
    if (msg)
        perror(msg);
    exit(status);
}

void    gc_clean_dustbin(t_dustbin **dustbin)
{
    t_dustbin   *tmp_free;
    if (!*dustbin || !dustbin)
        return ;
    while ((*dustbin))
    {
        tmp_free = (*dustbin);
        (*dustbin) = (*dustbin)->next;
        free(tmp_free->address);
        free(tmp_free);
    }
    (*dustbin) = NULL;
}

t_gc    *gc_adding_adress(t_gc *gc, void *address)
{
    t_dustbin   *dustbin;

    dustbin = malloc(sizeof(t_dustbin));
    if (! dustbin)
        return (NULL);
    dustbin->address = address;
    dustbin->next = NULL;
    if (gc->garbage)
    {
        dustbin->next = gc->garbage;
        gc->garbage = dustbin;
    }
    else
        gc->garbage = dustbin;
    return (gc);
}

void    *gc_filter(t_gc *gc, void *newaddress)
{
    if (!newaddress)
        return (NULL);
    if (!gc_adding_adress(gc, newaddress))
        return (NULL);
    return (newaddress);
}
