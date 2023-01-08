/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:55:23 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/08 18:54:41 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

// try to insert a node in tree;

void    insert(t_tree **root, t_tree *new)
{
    if (!root || *root)
        (*root) = new;
    else
    {
        if ((**root).left && !(**root).right)
            (**root).right = new;
        else if ((**root).right && !(**root).left)
            (**root).left = new;
        else
            (**root).right = new;
    }
}