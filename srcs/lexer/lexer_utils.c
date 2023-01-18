/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:02:31 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/18 00:52:06 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char    *whitespace(t_list *l_lexer, char *l_cmd)
{
    int len;

    len = 0;
    while (l_cmd[len] && ft_isspace(l_cmd[len]))
        len ++; 
    if (len)
        push_back(&l_lexer, creat_node(NULL, WSPACE));
    return (l_cmd + len);
}

char    *s_quote(t_list *l_lexer, char *l_cmd)
{
    int len;

    push_back(&l_lexer, creat_node(ft_strdup("\'"), SQUOTE));
    len = 0;
    while (l_cmd[len] && l_cmd[len] != NEWLINE && l_cmd[len] != '\'')
        len ++;
    if (len)
        push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WORD));
    if (l_cmd[len] == '\'')
        push_back(&l_lexer, creat_node(ft_strdup("\'"), SQUOTE));
    return (l_cmd + (len + (l_cmd[len] == '\'')));
}

char    *dollar(t_list  *l_lexer, char *l_cmd)
{
    int len;

    if (*(l_cmd + 1) == '?')
    {
        push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 2), RECENTEXC));
        return (l_cmd + 2);
    }
    len = 0;
    if (*l_cmd == DOLLAR)
        len ++;
    while (l_cmd[len] && (l_cmd[len] == '_' || ft_isalnum(l_cmd[len])))
        len ++;
    if (len)
        push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), VAR));
    else
    {
        push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 1), WORD));
        len ++;
    }
    return (l_cmd + len);
}

char    *d_quote(t_list *l_lexer, char *l_cmd)
{
    bool    mode;
    int     len;

    mode = false;
    len = 0;
    if (l_cmd[0] == '\"' && l_cmd[1] == '\"')
        mode = true;
    push_back(&l_lexer, creat_node(ft_strdup("\""), DQUOTE));
    while (l_cmd[len] && l_cmd[len] != NEWLINE && l_cmd[len] != '\"')
    {
        if (l_cmd[len] == DOLLAR)
        {
            if (len)
                push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WORD));
            l_cmd = dollar(l_lexer, l_cmd + len);
            len = 0;
        }
        else
            len ++;
    }
    if (len)
        push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WORD));
    if (mode)
        push_back(&l_lexer, creat_node(ft_strdup(""), WORD));
    if (l_cmd[len] == '\"' || mode)
        push_back(&l_lexer, creat_node(ft_strdup("\""), DQUOTE));
    return (l_cmd + (len + (l_cmd[len] == '\"')));
}

char    *normal_stat(t_list *l_lexer, char *l_cmd)
{
    bool    mode;
    int     len;

    mode = false;
    len = 0;
    while (l_cmd[len] && !ft_strchr("|&<>", l_cmd[len]) && !ft_isspace(l_cmd[len]))
    {
        if (l_cmd[len] == '*')
            mode = true;
        len ++;
    }
    if (!mode)
        push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WORD));
    else
        push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WILD));
    return (l_cmd + len);
}


