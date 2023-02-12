/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:48:38 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/30 15:32:58 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_rederct(int *io_infile, int *io_outfile, char *filename, t_token token)
{
	int	o_flag;
	int	*fds;

	o_flag = O_RDONLY;
	if (token & (APPEND | GREAT))
	{
		if (token & APPEND)
			o_flag = O_CREAT | O_RDWR | O_APPEND;
		else
			o_flag = O_CREAT | O_RDWR | O_TRUNC;
		return (*io_outfile = open(filename, o_flag, FILE_PERM));
	}
	if (token & LESS)
		return (*io_infile = open(filename, o_flag, FILE_PERM));
	fds = gc(g_global.gc, malloc(sizeof(int) * 2), TMP);
	if (!fds || herdoc(filename, fds) < 0)
		return (-1);
	return (*io_infile = fds[0]);
}

t_cmdexc    *merging_cmd(t_node **object)
{
    t_cmdexc    *new;
    char        **cmdexc;

    cmdexc = NULL;
    new = new_cmdexc(NULL, NODE_CMDEXC);
    if (!new)
        return (NULL);
    while ((*object) && (*object)->tok & (STRING | REDIRECT))
    {
        if ((*object)->tok & REDIRECT)
        {
            set_rederct(&new->io_src, &new->io_dest, (*object)->next->data,\
                (*object)->tok);
            (*object) = (*object)->next;
        }
        else if ((*object)->tok & (VAR | WORD | WILD))
            cmdexc = realloc_array(cmdexc, (*object)->data);
        (*object) = (*object)->next;
    }
    new->cmdexc = cmdexc;
    return (new);
}

t_exp   *expand(t_node  **object)
{
    t_grb   *n_grb;
    t_exp   *n_exp;
    
    n_exp = new_exp(NODE_CMDEXC);
    n_grb = new_grb();
    if (!n_exp || !n_grb || (*object)->tok & ENDOFCMD)
        return (NULL);
    while ((*object) && (*object)->tok & (STRING | PIPE | REDIRECT))
    {
        if ((*object)->tok & (REDIRECT | STRING))
            add_cmdexc_back(&n_grb, merging_cmd(object));
        else if ((*object)->tok & PIPE)
        {
            add_cmdexc_back(&n_grb, new_cmdexc(NULL, NODE_PIPE));
            (*object) = (*object)->next;
        }
        else
            (*object) = (*object)->next;
    }
    n_exp->grb = n_grb;
    return (n_exp);
}


int set_expand(t_expander *l_expander, t_lexer *l_lexer)
{
    t_node  *head;
    t_type  nature;

    l_lexer = quotes_removal(l_lexer);
	l_lexer = list_expansion(l_lexer);
	head = l_lexer->head;
	if (!head || head->tok & ENDOFCMD)
		return (EXIT_FAILURE);
    while (head && head->tok != ENDOFCMD)
    {
        if (head->tok & (REDIRECT | STRING | PIPE))
            add_back(&l_expander, expand(&head));
        else if (head->tok & (AND | OR))
        {
            nature = (head->tok == OR) * NODE_OR + (head->tok == AND) * NODE_AND;
            add_back(&l_expander, new_exp(nature));
            head = head->next;
        }
        else
            head = head->next;
    }
    add_back(&l_expander, new_exp(NODE_ENDOFCMD));
    return (EXIT_SUCCESS);
}

t_expander	*expander(t_lexer *l_lexer)
{
	t_expander *l_expander;
	int status;

    if (!l_lexer)
        return (NULL);
	l_expander = new_explist();
	if (!l_expander)
		return (NULL);
	status = set_expand(l_expander, l_lexer);
	if (status)
	{
		shleet_error("expander", "syntax error", 2);
		return (NULL);
	}
	return (l_expander);
}