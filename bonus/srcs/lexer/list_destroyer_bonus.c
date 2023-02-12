/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_destroyer_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:21:54 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:34:13 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_node	*delete_front(t_list *list)
{
	t_node	*target;

	if (!list->l_size)
		return (NULL);
	target = list->head;
	list->head = target->next;
	if (list->head)
		list->head->prev = NULL;
	(list->l_size)--;
	return (target);
}

t_node	*delete_back(t_list *list)
{
	t_node	*target;

	if (!list->l_size)
		return (NULL);
	target = list->buttom;
	list->buttom = target->prev;
	if (list->buttom)
		list->buttom->next = NULL;
	(list->l_size)--;
	return (target);
}

t_node	*delete_node(t_list *list, t_node *fordelete)
{
	if (!list || !fordelete)
		return (NULL);
	if (!fordelete->next)
		return (delete_back(list));
	if (!fordelete->prev)
		return (delete_front(list));
	fordelete->prev->next = fordelete->next;
	fordelete->next->prev = fordelete->prev;
	(list->l_size)--;
	return (fordelete);
}
