/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:57:19 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/09 19:01:13 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexer.h"


int handl_allocation(void   *ptr, char *error, int status)
{
    
}

void    insert_node(t_list **lst, t_list *next, t_list *prev)
{
    if (!lst || !*lst)
        return ;
    
}

t_list  *new_node(char *data)
{
    t_list  *node;

    node = malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->data = data;
    node->prev = NULL;
    node->size = 0;
    node->next = NULL;
    return (node);
}