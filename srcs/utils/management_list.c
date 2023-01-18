/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:15:42 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/17 18:33:30 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer *new_lexer(void)
{
    t_lexer *lexer;

    lexer = gc_filter(g_global.gc, malloc(sizeof(t_lexer)));
    if (! lexer)
        return (NULL);
    lexer->buttom = lexer->head = NULL;
    lexer->l_size = 0;
    return (lexer);
}

t_node *creat_node(char *data, t_token token)
{
    t_node  *n_node;

    n_node = gc_filter(g_global.gc, malloc(sizeof(t_node)));
    if (!n_node)
        return (NULL);
    n_node->data = data;
    n_node->next = n_node->prev = NULL;
    n_node->tok = token;
    return (n_node);
}

t_node  *get_node(t_node *crr_node, int mode)
{
    if (mode & LEFT)
    {
        if (!crr_node)
            return (NULL);
        while (crr_node->tok == WSPACE && crr_node)
            crr_node = crr_node->prev;
        return (crr_node);
    }
    else if (mode & RIGHT)
    {
        if (!crr_node)
            return (NULL);
        while (crr_node->tok == WSPACE && crr_node)
            crr_node = crr_node->next;
        return (crr_node);
    }
    return (NULL);
}

void    push_back(t_lexer **lexer, t_node *n_node)
{
    if (!(*lexer)->head)
        (*lexer)->head = n_node;
    else
    {
        (*lexer)->buttom->next = n_node;
        n_node->prev = (*lexer)->buttom;
    }
    (*lexer)->buttom = n_node;
    (*lexer)->l_size++;
}

void    print_lexer(t_node *node)
{
    int i;

    i = 1;
    if (!node)
        puts("ERROR IN PRIN_lexer");
    while(node)
    {
        printf("AFFICHE node |%d| type >>(%c)<< -> >>(%s)<<\n\n",i, (char)node->tok, node->data);
        i ++;
        node = node->next;
    }   
}
