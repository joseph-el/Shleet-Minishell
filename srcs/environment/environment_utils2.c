/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:29:55 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/28 22:35:09 by aelkhali         ###   ########.fr       */
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
        (*target_node) = (*target_node)->next;
        (*target_node)->prev = NULL;
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
        if (!ft_strncmp(type, tmp->type, ft_strlen(type) + 1))
            return (delete_environment(&tmp), EXIT_SUCCESS);
        tmp = tmp->next;
    }
    return (true);
}

int size_environment(t_env *head)
{
	int i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

t_env   *last_environment(t_env *head)
{
    if (!head)
       return (NULL);
    while (head->next)
        head = head->next;
    return (head);
}
