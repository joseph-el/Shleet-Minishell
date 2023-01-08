/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:53:11 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/08 13:55:13 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tree.h"

t_tree  *ft_newnode(char **data)
{
    t_tree  *new;

    new = malloc(sizeof(t_tree));
    if (!new)
        return (NULL);
    new->data = data;
    new->left = new->right = NULL;
    return (new);
}