/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:29:55 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/27 20:43:41 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    delete_environment(t_env **target_node)
{
    t_env   *t_next;
    
    if (!(*target_node)->next)
    {
        (*target_node)->prev->next = NULL;
        (*target_node)->prev = NULL;
        return ;
    }
    if (!(*target_node)->prev)
    {
        (*target_node)->next = (*target_node);
        (*target_node)->next = NULL;
        return ;
    }
    t_next = (*target_node)->next;
    (*target_node)->prev->next = t_next;
    (*target_node)->prev = NULL;
    (*target_node)->next = NULL;
}

int remove_environment(t_env **environment, char *type)
{
    t_env   *tmp;

    if (!environment || !type)
        return (false);
    if (!find_environment(*environment, type))
        return (false);
    tmp = (*environment);
    while (tmp)
    {
        if (!ft_strcmp(type, tmp->type))
            return (delete_environment(tmp), 0);
        tmp = tmp->next;
    }
    return (true);
}
