/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:24:27 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/28 16:23:00 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env   *new_environment(char *content, char *type)
{
    t_env   *node_environment;

    // node_environment = malloc(sizeof(t_env));
    node_environment = gc(g_global.gc, malloc(sizeof(t_env)), OVR);
    if (!node_environment)
        return (NULL);
    node_environment->next = NULL;
    node_environment->prev = NULL;
    node_environment->content = content;
    node_environment->type = type;
    return (node_environment);
}

t_env   *insert_environment(t_env **environment, char *type, char *content)
{
    t_env   *tmp_environment;
    t_env   *new_env;

    if (*environment == NULL)
    {
        new_env = new_environment(content, type);
        return (*environment = new_env, NULL);
    }
    tmp_environment = (*environment);
    while (tmp_environment->next)
        tmp_environment = tmp_environment->next;
    new_env = new_environment(content, type);
    tmp_environment->next = new_env;
    new_env->prev = tmp_environment;
    return (*environment);
}

t_env   *init_environment(char **env)
{
    t_env   *environment;
    int     index;

    if (!env)
        return (NULL);
    environment = NULL;
    index = -1;
    while (env && env[++index])
        insert_environment(&environment, type_environment(env[index]), \
             content_environment(env[index]));
    return (environment);
}
