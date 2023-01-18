/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:46:48 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/18 01:18:06 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

// bool    search(t_node *current, t_token token)
// {
//     if (!current)
//         return (false);
//     while (current)
//     {
//         if (token == current->tok)
//             return (true);
//         current = current->next;
//     }
//     return (false);
// }

/* check the valide syntax of: | && || */

bool connector_syntax(t_node *crr_node)
{
    t_token tok;
    t_node  *l_node;
    t_node  *r_node;

    tok = crr_node->tok;
    if (!(tok & CONNECTOR))
        return (true);
    l_node = get_node(crr_node->prev, LEFT);
    r_node = get_node(crr_node->next, RIGHT);
    if (!(l_node->tok & (STRING | RPAR)))       
        return (gc_error(UNEXPECTED_TOKEN, crr_node->data, 2), false); 
    if (!(r_node->tok & (STRING | REDIRECT | RPAR | LPAR)))
        return (gc_error(UNEXPECTED_TOKEN, crr_node->data, 2), false);
    return (true);
}

/* check the valide syntax of: > < >> << */

bool    redirect_syntax(t_node  *crr_node)
{
    t_node  *r_node;
    t_token tok;

    tok = crr_node->tok;
    if (!(tok & REDIRECT))
        return (true);
    r_node = get_node(crr_node->next, RIGHT);
    if (!r_node)
        return (gc_error(UNEXPECTED_TOKEN, crr_node->data, 2), false);
    if (!(r_node->tok & STRING))
        return (gc_error(UNEXPECTED_TOKEN, crr_node->data, 2), false);
    return (true);
}

/* check the valide syntax of: " and ' */

bool    quote_syntax(t_node *crr_node, int *remember)
{
    t_token tok;
    int     s_quotes;
    int     d_quotes;

    s_quotes = 0;
    d_quotes = 0;
    tok = crr_node->tok;
    if (!(tok & (SQUOTE | DQUOTE)))
        return (true);
    while (crr_node->tok != ENDOFCMD && !*remember)
    {
        if (crr_node->tok & SQUOTE)
            s_quotes ++;
        else if (crr_node->tok & DQUOTE)
            d_quotes ++;
        crr_node = crr_node->next;
    }
    if (s_quotes % 2)
        return (gc_error(UNCLOSED_SQ, "\'`", 2), false);
    if (d_quotes % 2)
        return (gc_error(UNCLOSED_DQ, "\"`", 2), false);
    *remember += 1;
    return (true);
}

/* check the valide syntax of: ( ) */

bool    g_parentheses(t_node *crr_node)
{
    int     state;
    bool    found;

    if (!(crr_node->tok & (LPAR | RPAR)))
        return (true);
    state = 0;
    found = false;
    while (crr_node->tok != ENDOFCMD)
    {
        if (crr_node->tok & LPAR)
            state += 1;
        else if (crr_node->tok & RPAR)
            state -= 1;
        if (crr_node->tok & RPAR)
        {
            found = true; 
            break;
        }
        if (state < 0)
            return (gc_error(UNEXPECTED_TOKEN, ")", 2), false);
        crr_node = crr_node->next;
    }
    if (!found)
        return (gc_error(UNEXPECTED_TOKEN, "(", 2), false);
    return (true);
}

/*The gc_error for print errors*/

void	gc_error(char *error_msg, char *specify, int status)
{
	ft_putstr_fd("Shleet-Minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	if (specify)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(specify, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

/*syntax of cmdline*/

int syntax(t_lexer *l_lexer)
{
    static int  remember;
    static int  test;
    t_node      *saving;
    int         error;
    bool        r_true;

    error = -1;
    saving = l_lexer->head;
    remember = 0;
    test = 0;
    r_true = false;
    while (saving->tok != ENDOFCMD)
    {
        r_true = (quote_syntax(saving, &remember) && g_parentheses(saving));
        error = (redirect_syntax(saving) && connector_syntax(saving) && r_true == true);
        if (!error)
            return (false);
        saving = saving->next;
    }
    return ((r_true == true));
}