/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:46:48 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/16 14:20:00 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#define LEFT 1
#define RIGHT 4

bool    search(t_node *current, t_token tok)
{
    while (current)
    {
        if (tok == current->tok)
            return (true);
        current = current->next;
    }
    return (false);
}

// t_node  *get_node(t_node *crr_node, int mode)
// {
//     if (mode & LEFT)
//     {
//         if (!crr_node->prev)
//             return ( NULL);
//         else
//             while (crr_node->tok == WSPACE && crr_node->prev)
//                 crr_node = crr_node->prev;
//         if (crr_node->prev)
//                 return (crr_node->prev);
//         else
//             return (NULL);
//     }
//     else if (mode & RIGHT)
//     {
//         if (!crr_node->next)
//             return (NULL);
//         else
//             while (crr_node->tok == WSPACE && crr_node->next)
//                 crr_node = crr_node->next;
//             if (crr_node->next)
//                 return (crr_node->next);
//             else
//                 return (NULL);        
//     }
//     return (NULL);
// }

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

bool    quote_syntax(t_node *crr_node)
{
    t_token tok;
    bool    stat;
    
    tok = crr_node->tok;
    stat = search(crr_node, tok);
    if (!stat && tok == SQUOTE)
        return (ft_putstr_fd(UNCLOSED_SQ, 2), false);
    else if (!stat && tok == DQUOTE)
        return (ft_putstr_fd(UNCLOSED_DQ, 2), false);
    return (true);
}


bool connector_syntax(t_node *crr_node)
{
    t_node  *l_node;
    t_node  *r_node;
    t_token tok;

    l_node = get_node(crr_node->prev, LEFT);

    r_node = get_node(crr_node->next, RIGHT);
    tok = crr_node->tok;
    if (l_node->tok != WORD || l_node->tok != WILD || l_node->tok != SQUOTE || l_node->tok != DQUOTE)       
        return (ft_putstr_fd(UNEXPECTED_TOKEN, 2), false);
        
    else if (r_node->tok != WORD || r_node->tok != WILD || r_node->tok != SQUOTE || r_node->tok != DQUOTE \
        || r_node->tok != LESS || r_node->tok != GREAT || r_node->tok != REGREAT || r_node->tok != RELESS)
        return (ft_putstr_fd(UNEXPECTED_TOKEN, 2), false);
    return (true);
}

bool    redirect_syntax(t_node  *crr_node)
{
    t_node  *getting;
    t_token tok;

    tok = crr_node->tok;
    getting = get_node(crr_node,new_lexer, RIGHT);
    if (!getting)
        return (ft_putstr_fd(UNEXPECTED_TOKEN, 2), false);
    if (getting->tok != WORD || getting->tok != WILD || getting->tok != SQUOTE || getting->tok != DQUOTE)
        return (ft_putstr_fd(UNEXPECTED_TOKEN, 2), false);
    return (true);
}

int syntax(t_lexer *l_lexer)
{
    t_node  *saving;
    int     error;

    error = -1;
    saving = l_lexer->head;
    while (saving)
    {
        if (saving->tok == SQUOTE || saving->tok == DQUOTE)
        {
            error = quote_syntax(saving);
        }
        else if (saving->tok == LESS || saving->tok == GREAT || saving->tok == RELESS)
        {
            error = redirect_syntax(saving);
        }
        else if (saving->tok == AND || saving->tok == PIPE || saving->tok == OR)
        {
            puts("iam here");
            error = connector_syntax(saving);
        }
        saving = saving->next;
        if (!error)
            return (puts("flase"), false);
    }
    return (true);
}