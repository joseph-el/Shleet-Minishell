/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:56:05 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/29 18:47:21 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    run_logical(t_grb *left, t_grb *right, t_type type)
{
    executor(left, type, E_LOGICAL);
    if (type & NODE_AND)
    {
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) == 0)
            executor(right, type, E_LOGICAL);
    }
    else
    {
        if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) != 0)
            executor(right, type, E_LOGICAL);
    }
}


int controller(t_expander *l_expander)
{
    t_exp   *head;

    head = l_expander->head;
    if (!head || head->nature & NODE_ENDOFCMD)
        return (EXIT_FAILURE);
    while (head && head->nature != NODE_ENDOFCMD)
    {
        if (head->next && head->next->nature & (NODE_AND | NODE_OR))
        {
            executor(head->next, E_LOGICAL);
            head = head->next->next;
        }
        else if (head->nature & NODE_CMDEXC)
        {
            executor(head, E_GRB);
            head = head->next;
        }
    }
    return (EXIT_SUCCESS);
}

