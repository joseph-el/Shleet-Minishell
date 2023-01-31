/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:21:11 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/29 18:19:03 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list  *quotes_removal(t_list *e_list)
{
    t_node  *target;
    t_node  *next;

    target = e_list->head;
    while (target->tok != ENDOFCMD)
    {
        if (target->tok & (SQUOTE | DQUOTE | LPAR | RPAR))
            next = delete_node(e_list, target)->next;
        else
            next = target->next;
        target = next;
    }
    return (e_list);    
}

t_node  *fill_content(t_list *l_list, t_node *object)
{
    if (!object)
        return (NULL);
    if (object->prev && object->prev->tok & VAR && object->tok != HERDOC)
    {
        object->prev->data = get_environment(g_global.envp, object->prev->data + 1);
        if (!object->prev->data)
            object->prev->data = gc(g_global.gc, ft_strdup(""), TMP);
        return (object);
    }
    while (object && object->tok & (WORD | VAR))
    {
        if (object->tok & VAR && get_node(object->prev, LEFT)->tok != HERDOC)
        {
            object->data = get_environment(g_global.envp, object->data + 1); 
            if (!object->data)
                object->data = gc(g_global.gc, ft_strdup(""), TMP);
        }
        object->prev->data = gc(g_global.gc, \
            ft_strjoin(object->prev->data, object->data), TMP);
        object = delete_node(l_list, object)->next;
    }
    return (object->prev);
}

t_lexer  *list_expansion(t_lexer *l_list)
{
    t_node  *head;
    t_node  *next;

    head = l_list->head;
    while (head && head->tok != ENDOFCMD)
    {
        if (head->tok & STRING)
        {
            if (head->tok & (WORD | VAR))
                head = fill_content(l_list, head->next);
            else if (head->tok & WILD)
            {
                if (head->prev && head->prev->tok & REDIRECT)
                    head->tok = WORD;
                else
                    head = wildcard(head);
            }
        }
        if (head->tok & WSPACE)
            next = delete_node(l_list, head)->next;
        else
            next = head->next;
        head = next;
    }
    return (l_list);
}