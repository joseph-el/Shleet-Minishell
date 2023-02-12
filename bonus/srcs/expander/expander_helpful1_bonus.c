/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpful1_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:12:55 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:33:46 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_cmdexc	*merging_cmd(t_node **object)
{
	t_cmdexc	*new;
	char		**cmdexc;

	cmdexc = NULL;
	new = new_cmdexc(NULL, NODE_CMDEXC);
	if (!new)
		return (NULL);
	while ((*object) && (*object)->tok & (STRING | REDIRECT))
	{
		if ((*object)->tok & REDIRECT)
		{
			set_rederct(&new->io_src, &new->io_dest, (*object)->next->data,
				(*object)->tok);
			(*object) = (*object)->next;
		}
		else if ((*object)->tok & (VAR | WORD | WILD))
			cmdexc = realloc_array(cmdexc, (*object)->data, (*object)->tok);
		(*object) = (*object)->next;
	}
	new->cmdexc = cmdexc;
	return (new);
}

t_exp	*expand(t_node **object)
{
	t_grb	*n_grb;
	t_exp	*n_exp;

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

int	set_expand(t_expander *l_expander, t_lexer *l_lexer)
{
	t_node	*head;
	t_type	nature;

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
			nature = (head->tok == OR) * NODE_OR + (head->tok == AND)
				* NODE_AND;
			add_back(&l_expander, new_exp(nature));
			head = head->next;
		}
		else
			head = head->next;
	}
	return (EXIT_SUCCESS);
}
