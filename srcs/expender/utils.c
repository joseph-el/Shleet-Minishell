/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:51:39 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/18 00:53:58 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool    search(t_node *current, t_token token)
{
    if (!current)
        return (false);
    while (current)
    {
        if (token == current->tok)
            return (true);
        current = current->next;
    }
    return (false);
}