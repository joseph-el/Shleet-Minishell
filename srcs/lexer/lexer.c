/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:29 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/17 00:25:56 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char    *handle_state(t_list *l_lexter, char *l_cmd)
{
    t_token tok1;
    t_token tok2;
    t_token type;
    int     *target;

    target = gc_filter(g_global.gc, malloc(sizeof(int)  * 2));
    if (!target)
        return (NULL);
    target[0] = *l_cmd;
    target[1] = *(l_cmd + 1);
    tok1 = (*target == PIPE) * PIPE + (*target == GREAT) \
        * GREAT + (*target ==  LESS) * LESS + (*target == SAND) * SAND;
    tok2 = (target[1] == GREAT) * GREAT + (target[1] == LESS) \
        * LESS + (target[1] == PIPE) * PIPE + (target[1] == SAND) * SAND;
    type = ((tok1 + tok2) + 1 == REGREAT) * REGREAT + ((tok1 + tok2)  == RELESS) \
         * RELESS + ((tok1 + tok2) == OR) * OR + ((tok1 + tok2)  == AND) * AND;
    if (tok1 && tok2)
        push_back(&l_lexter, creat_node(ft_strndup(l_cmd, 2), type));
    else if (tok1)
        push_back(&l_lexter, creat_node(ft_strndup(l_cmd, 1), type));
    return (l_cmd + ((tok1 && tok2) + (tok1 != 0)));
}

t_list  *set_token(char *l_cmd)
{
    t_list  *l_lexer;

    l_lexer = new_lexer();
    if (!l_lexer)
        return (NULL);
    push_back(&l_lexer, creat_node(NULL, BEGINOFCMD));
    while (*l_cmd && *l_cmd != NEWLINE)
    {
        if (ft_isspace(*l_cmd))
            l_cmd = whitespace(l_lexer, l_cmd);
        else if (*l_cmd == SQUOTE)      
            l_cmd = s_quote(l_lexer, l_cmd + 1);
        else if (*l_cmd == DQUOTE)
            l_cmd = d_quote(l_lexer, l_cmd + 1);
        else if (*l_cmd == DOLLAR)
            l_cmd = dollar(l_lexer, l_cmd);
        else if (ft_strchr("<|>&", *l_cmd))
            l_cmd = handle_state(l_lexer, l_cmd);
        else
            l_cmd = normal_stat(l_lexer, l_cmd);
    }
    push_back(&l_lexer, creat_node(NULL, ENDOFCMD));
    return (l_lexer);
}

t_lexer *lexer(char *cmdline)
{
    t_lexer *l_lexer;
    bool    syn;

    l_lexer = set_token(cmdline);
    if (!l_lexer)
        return  (NULL);
    syn = syntax(l_lexer);
    if (!syn)
        return (NULL);
    return (l_lexer);
}