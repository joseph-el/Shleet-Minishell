 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:00:03 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/29 17:22:47 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expander  *new_explist(void)
{
    t_expander  *l_expander;

    l_expander = gc(g_global.gc, malloc(sizeof(t_expander)), TMP);
    if (! l_expander)
        return (NULL);
    l_expander->head = NULL;
    l_expander->head = NULL;
    return (l_expander);
}

t_grb   *new_grb(void)
{
    t_grb *l_grb;

    l_grb = gc(g_global.gc, malloc(sizeof(t_grb)), TMP);
    if (!l_grb)
        return (NULL);
    l_grb->head = NULL;
    l_grb->tail = NULL;
    return (l_grb);
}

t_exp   *new_exp(t_type nature)
{
    t_exp   *exp;

    exp = gc(g_global.gc, malloc(sizeof(t_exp)), TMP);
    if (!exp)
        return (NULL);
    exp->next = exp->prev = NULL;
    exp->grb = NULL;
    exp->nature = nature;
    return (exp);
}

t_cmdexc    *new_cmdexc(char **target, t_type nature)
{
    t_cmdexc    *cmdexc;
    
    cmdexc = gc(g_global.gc, malloc(sizeof(t_cmdexc)), TMP);
    if (!cmdexc)
        return (NULL);
    cmdexc->next = cmdexc->prev = NULL;
    cmdexc->cmdexc = target;
    cmdexc->io_src = STDIN_FILENO;
    cmdexc->io_dest = STDOUT_FILENO;
    cmdexc->node_type = nature;
    return (cmdexc);
}

void    add_back(t_expander **expander, t_exp *n_exp)
{
    if (!(*expander)->head)
        (*expander)->head = n_exp;
    else
    {
        (*expander)->tail->next = n_exp;
        n_exp->prev = (*expander)->tail;
    }
    (*expander)->tail = n_exp;
}

