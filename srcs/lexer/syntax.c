/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:55:07 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 20:02:10 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	connector_syntax(t_node *crr_node)
{
	t_node	*l_node;
	t_node	*r_node;

	if (!(crr_node->tok & CONNECTOR))
		return (true);
	l_node = get_node(crr_node->prev, LEFT);
	r_node = get_node(crr_node->next, RIGHT);
	if (!(l_node->tok & (STRING | RPAR)))
		return (shleet_error(UNEXPECTED_TOKEN, crr_node->data, 2), false);
	if (!(r_node->tok & (STRING | REDIRECT | LPAR)))
		return (shleet_error(UNEXPECTED_TOKEN, crr_node->data, 2), false);
	return (true);
}

bool	redirect_syntax(t_node *crr_node)
{
	t_node	*r_node;

	if (!(crr_node->tok & REDIRECT))
		return (true);
	r_node = get_node(crr_node->next, RIGHT);
	if (!r_node)
		return (shleet_error(UNEXPECTED_TOKEN, crr_node->data, 2), false);
	if (!(r_node->tok & STRING))
		return (shleet_error(UNEXPECTED_TOKEN, crr_node->data, 2), false);
	return (true);
}

bool	quote_syntax(t_node *crr_node)
{
	int	s_quotes;
	int	d_quotes;

	s_quotes = d_quotes = 0;
	while (crr_node->tok != ENDOFCMD)
	{
		if (crr_node->tok & SQUOTE)
			s_quotes++;
		else if (crr_node->tok & DQUOTE)
			d_quotes++;
		crr_node = crr_node->next;
	}
	if (s_quotes % 2)
		return (shleet_error(UNCLOSED_SQ, "\'`", 2), false);
	if (d_quotes % 2)
		return (shleet_error(UNCLOSED_DQ, "\"`", 2), false);
	return (true);
}

bool    g_parentheses(t_node *crr_node, t_node *left, t_node *right, int flag)
{
    int     l_par;
    int     r_par;
    
    l_par = r_par = 0;
    if (flag & COUNTER)
    {
        while (crr_node)
        {
            l_par += (crr_node->tok == LPAR);
            r_par += (crr_node->tok == RPAR);
            crr_node = crr_node->next;
        }
		l_par += r_par;
        return (!(l_par % 2));
    }
    if (!(crr_node->tok & (LPAR | RPAR)))
        return (true);
    if (crr_node->tok & LPAR && left->tok & (BEGINOFCMD | CONNECTOR | LPAR) \
		&& right->tok & (STRING | REDIRECT | LPAR))
        return (true);
    if (crr_node->tok & RPAR && left->tok & (STRING | RPAR) && right->tok \
		& (CONNECTOR | RPAR | ENDOFCMD))
        return (true);
    return (shleet_error(UNEXPECTED_TOKEN, "`()`", 2), false);
}

int	syntax(t_lexer *l_lexer)
{
	t_node  *head;
    t_node  *right;
    t_node  *left;
	int     error;

	head = l_lexer->head;
	error = -1;
	if (!quote_syntax(head))
		return (false);
	if (!g_parentheses(head, NULL, NULL, COUNTER))
		return (shleet_error(UNEXPECTED_TOKEN, "`()`", 2), false);
	while (head->tok != ENDOFCMD)
	{
        right = get_node(head->next, RIGHT);
        left = get_node(head->prev, LEFT);
        error = (redirect_syntax(head) && connector_syntax(head) \
            && g_parentheses(head, left, right, 0)) ;
        if (!error)
			return (false);
		head = head->next;
	}
	return (true);
}