/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:27:54 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/27 20:43:03 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *type_environment(char *_env)
{
    int i;

    if (!_env)
        return (NULL);
    i = 0;
    while (_env[i] && _env[i] != '=')
        i ++;
    i += (_env[i] == '=');
    return (ft_strndup(_env, i));
}

char    *content_environment(char *_env)
{
    if (!_env)
        return (NULL);
    while (*_env && *_env != '=')
        _env ++;
    _env += (*_env == '=');
    return (ft_strdup(_env));
}

char    *get_environment(t_env *environment, char *type)
{
    if (!environment || !type)
        return (NULL);
    while (environment)
    {
        if (!ft_strcmp(environment->type, type))
            return (environment->content);
        environment = environment->next;
    }
    return (NULL);
}

t_env    *find_environment(t_env *environment, char *type)
{
    if (!environment || !type)
        return (NULL);
    while (environment)
    {
        if (!ft_strcmp(environment->type, type))
            return (environment);
        environment = environment->next;
    }
    return (NULL);
}

void    print_environment(t_env *environment)
{
    if (!environment)
        return ;
    while (environment)
    {
        ft_putstr_fd(environment->type, STDOUT_FILENO);
        ft_putstr_fd("=", STDOUT_FILENO);
        ft_putstr_fd(environment->content, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        environment = environment->next;
    }
}
