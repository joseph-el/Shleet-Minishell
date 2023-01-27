/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:51:29 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/27 17:25:31 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_exp   *new_exp(t_type node_type)
{
    t_exp   *new_exp;

    new_exp = gc(g_global.gc, malloc(sizeof(t_exp)), TMP);
    if (!new_exp)
        return (NULL);
    new_exp->next = new_exp->prev = NULL;
    new_exp->io_inf = STDIN_FILENO;
    new_exp->io_out = STDOUT_FILENO;
    new_exp->connector = NULL;
    new_exp->node_type = node_type;
    return (new_exp);
}

t_connector *new_connector(t_exp *left, t_exp *right, t_token type)
{
    t_connector *connector;

    connector = gc(g_global.gc, malloc(sizeof(t_connector)), TMP);
    if (!connector)
        return (NULL);
    connector->left = left;
    connector->right = right;
    connector->type = type;
    return (connector);
}

void    add_back(t_expander **expander, t_exp *n_node)
{
    if (!(*expander)->head)
        (*expander)->head = n_node;
    else
    {
        (*expander)->tail->next = n_node;
        n_node->prev = (*expander)->tail;
    }
    (*expander)->tail = n_node;
}