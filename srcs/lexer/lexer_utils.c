/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:49:29 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/12 16:50:02 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexer.h"

void    insert_node(t_list  **lst, t_list *node, t_adress *index, int mode)
{
    t_list  *tmp;

    tmp = (*lst);
    if (mode & N_FRONT && lst)
        (*lst) = node;
    else if (mode & N_BACK)
    {
        if (!*lst)
            insert_node(lst, node, NULL, N_FRONT);
        else
        {
            while (tmp)
                tmp = tmp->next;
            tmp->next = node;
            node->prev = tmp;
        }
    }
    else if ((mode & N_PALCE) && lst && index)
    {
        index->next = NULL;
        index->prev = node;
    }
}

short index(char c)
{
    int token1;
	int token2;
    
    token1 = (c == '|') * PIPE + (c == '&') * BG + (c == '>') \
        * GREAT + (c == '<') * LESS + (c == ';') * FG;

    token2 = (c == '|') * OR + (c == '&') * AND + (c == '>') \
        * DGREAT + (c == '<') * DLESS + (c == ';') * DSEMI;
    
    return ((1 >> 2) & (token1 | token2));
}

t_list  *newnode(char *cmd, t_token token)
{
    t_list  *node;

    if (!cmd)
        return (NULL);
    node = malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->data = cmd;
    node->next = NULL;
    node->prev = NULL;
    node->token = token;
    return (node);
}