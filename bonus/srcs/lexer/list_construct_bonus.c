/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_construct_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:15:42 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:34:11 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_list	*new_list(void)
{
	t_list	*list;

	list = gc(g_global.gc, malloc(sizeof(t_list)), TMP);
	if (!list)
		return (NULL);
	list->buttom = NULL;
	list->head = NULL;
	list->l_size = 0;
	return (list);
}

t_node	*creat_node(char *data, t_token token)
{
	t_node	*n_node;

	n_node = gc(g_global.gc, malloc(sizeof(t_node)), TMP);
	if (!n_node)
		return (NULL);
	gc_adding_adress(g_global.gc, data, TMP);
	n_node->data = data;
	n_node->next = NULL;
	n_node->prev = NULL;
	n_node->tok = token;
	return (n_node);
}

t_node	*get_node(t_node *crr_node, int mode)
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

void	push_back(t_lexer **lexer, t_node *n_node)
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
