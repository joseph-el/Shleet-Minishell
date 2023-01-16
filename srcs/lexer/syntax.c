/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:46:48 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/17 00:47:25 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

bool    search(t_node *current, t_token tok)
{
    if (!current)
        return (false);
    while (current)
    {
        if (tok == current->tok)
            return (true);
        current = current->next;
    }
    return (false);
}

bool    quote_syntax(t_node *crr_node, int *remember)
{
    t_token     tok;
    bool        state;
    
    tok = crr_node->tok;
    state = search(crr_node->next, tok);
    *remember += 1;

    if (!state && tok == SQUOTE && *remember % 2)
        return (ft_putstr_fd(UNCLOSED_SQ, 2), false);
    if (!state && tok == DQUOTE && *remember % 2)
        return (ft_putstr_fd(UNCLOSED_DQ, 2), false);
    return (true);
}

bool connector_syntax(t_node *crr_node)
{
    t_node  *l_node;
    t_node  *r_node;

    l_node = get_node(crr_node->prev, LEFT);
    r_node = get_node(crr_node->next, RIGHT);

    if (l_node->tok != WORD && l_node->tok != WILD && l_node->tok != SQUOTE && l_node->tok != DQUOTE && l_node->tok != VAR)       
        return (ft_putstr_fd(UNEXPECTED_TOKEN, 2), false);
        
    if (r_node->tok != WORD && r_node->tok != WILD && r_node->tok != SQUOTE && r_node->tok != DQUOTE \
        && r_node->tok != LESS && r_node->tok != GREAT && r_node->tok != REGREAT && r_node->tok != RELESS)
        return (ft_putstr_fd(UNEXPECTED_TOKEN, 2), false);
    
    return (true);
}

bool    redirect_syntax(t_node  *crr_node)
{
    t_node  *getting;
    t_token tok;

    tok = crr_node->tok;
    getting = get_node(crr_node->next, RIGHT);
    if (!getting)
        return (ft_putstr_fd(UNEXPECTED_TOKEN, 2), false);
    if (getting->tok != WORD && getting->tok != WILD && getting->tok != SQUOTE && getting->tok != DQUOTE)
        return ( ft_putstr_fd(UNEXPECTED_TOKEN, 2), false);
    return (true);
}

int syntax(t_lexer *l_lexer)
{
    static int  remember;
    t_node      *saving;
    int         error;

    error = -1;
    saving = l_lexer->head;
    remember = 0;
    while (saving)
    {
        if (saving->tok == SQUOTE || saving->tok == DQUOTE)
            error = quote_syntax(saving, &remember);
        else if (saving->tok == LESS || saving->tok == GREAT || saving->tok == REGREAT || saving->tok == RELESS)
            error = redirect_syntax(saving);
        else if (saving->tok == AND || saving->tok == PIPE || saving->tok == OR)
            error = connector_syntax(saving);
        if (!error)
            return (false);
        saving = saving->next;
    }
    return (true);
}