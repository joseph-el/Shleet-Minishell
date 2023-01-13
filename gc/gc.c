/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:04:11 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/14 00:14:07 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gc.h"

// void    (*adding)(struct s_gc **, void *, int mode)
// {
//     return (NULL);
// }

/** test the global struct **/

t_global	g_global = {.gc = NULL, .program_name = NULL, .status = 0, .is_running = 0};

void prin(t_dustbin *ls)
{
    while (ls)
    {
        printf("AFFICHE |%s|\n", (char *)ls->adress);
        ls = ls->next;
    }
}

void    clean_dustbin(t_dustbin **dustbin)
{
    t_dustbin   *tmp;
    
    while (*dustbin)
    {
        tmp = (*dustbin);
        printf("check free adress |%p|\n", tmp->adress);
        (*dustbin) = (*dustbin)->next;
        free(tmp->adress);
        free(tmp);
    }
    (*dustbin) = NULL;
}

t_gc    *adding(t_gc *gc, void *ptr)
{
    t_dustbin   *dustbin;

    if (!gc || !ptr)
        return (NULL);
    dustbin = malloc(sizeof(t_dustbin));
    if (!dustbin)
        return (NULL);
    dustbin->adress = ptr;
    dustbin->next = NULL;
    if (!gc->garbage)
        gc->garbage = dustbin;
    else
    {
        dustbin->next = gc->garbage;
		gc->garbage = dustbin;
    }
    return (gc);
}

t_gc    *gc_init(void)
{
    t_gc    *gc;

    gc = malloc(sizeof(t_gc));
    if (!gc)
        return (NULL);
    gc->adding = &adding;
    gc->clean_dustbin = &clean_dustbin;
    gc->garbage = NULL;
    return (gc);
}

void    *gc_filter(t_gc *gc, void *ptr, char *msg)
{
    if (!ptr)
        return (puts(msg), NULL);
    if (!adding(g_global.gc, ptr))
        return (puts(msg), NULL);
    return (ptr);
}

int main(int ac, char **args, char **env)
{
    char    *test;
    int     *tab;
    
    // g_global.is_running = true;
    // g_global.status = EXIT_SUCCESS;
    // g_global.program_name = args[0];


    g_global.gc = gc_init();
    
    test = gc_filter(g_global.gc, strdup("Hello 1"), "Malloc");
    //puts(test);
    //printf("%p\n", test);
    //free(test);
    
    test = gc_filter(g_global.gc, strdup("Hello 2"), "Malloc");
    //puts(test);
    //printf("%p\n", test);
    //free(test);

    test = gc_filter(g_global.gc, strdup("Hello 333"), "Malloc");
    //puts(test);
    //printf("%p\n", test);
    //free(test);

    prin(g_global.gc->garbage);
    
    
    /* This */
    
    /*--------------------------------*/
    clean_dustbin(&g_global.gc->garbage);
    /*--------------------------------*/
    
    free(g_global.gc);

    system("leaks gc");
    return (EXIT_SUCCESS);
}