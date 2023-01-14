/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:17:48 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/14 20:03:40 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc/include/gc.h"
#include <string.h>

int main()
{
    char *test;


    // test = strdup("hhhehhh");
    // test = strdup("fdf");
    t_gc *gc;

    gc = gc_init();
    


    str = gc_filter(gc, malloc(diseofg(hcsart)));
    

    
    test = gc_filter(gc, strdup("heeee"));
    test = gc_filter(gc, strdup("hefdfdfeee"));
    
    gc_clean_dustbin(&gc->garbage);

    free(gc);
    system("leaks a.out");
    return (0);
}