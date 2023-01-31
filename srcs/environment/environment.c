/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:24:27 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/29 21:40:05 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env   *new_environment(char *content, char *type)
{
    t_env   *node_environment;

    node_environment = gc(g_global.gc, malloc(sizeof(t_env)), OVR);
    if (!node_environment)
        return (NULL);
    node_environment->next = NULL;
    node_environment->prev = NULL;
    node_environment->content = content;
    node_environment->type = type;
    node_environment->is_var = 0;
    return (node_environment);
}

t_env   *insert_environment(t_env **environment, char *type, char *content, char *env)
{
    t_env   *tmp_environment;
    t_env   *new_env;

    if (*environment == NULL)
    {
        new_env = new_environment(content, type);
        if(ft_strchr(env, '='))
            new_env->is_var = 1;
        return (*environment = new_env, NULL);
    }
    tmp_environment = (*environment);
    while (tmp_environment->next)
        tmp_environment = tmp_environment->next;
    new_env = new_environment(content, type);
    if(ft_strchr(env, '='))
        new_env->is_var = 1;
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
        content_environment(env[index]), env[index]);
    /**
     * @brief fix when Shleet doesn’t find the PATH
     * 
     */
    // if (!find_environment(environment, "PATH"))
    //     insert_environment(&environment, gc(g_global.gc, ft_strdup("PATH"), OVR), gc(g_global.gc, ft_strdup(_PATH_STDPATH), OVR), WHAT IS THAT ?)
    
    return (environment);
}
