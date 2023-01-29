/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:27:54 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/29 15:15:33 by aelkhali         ###   ########.fr       */
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
        i++;
    return (ft_strndup(_env, i));
}

char    *content_environment(char *_env)
{
    if (!_env)
        return (NULL);
    while (*_env && *_env != '=')
        _env++;
    _env += (*_env == '=');
    return (ft_strdup(_env));
}

char    *get_environment(t_env *environment, char *type)
{
    if (!environment || !type)
        return (NULL);
    while (environment)
    {
        if (!ft_strncmp(environment->type, type, ft_strlen(type) + 1))
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
        if (!ft_strncmp(environment->type, type, ft_strlen(type) + 1))  
            return (environment);
        environment = environment->next;
    }
    return (NULL);
}

void    print_environment(t_env *environment, int fd)
{
    if (!environment)
        return ;
    while (environment)
    {
        if (environment->is_var)
            ft_putstr_fd(environment->type, fd);
        if (*environment->content)
        {
            ft_putstr_fd("=", fd);
            ft_putstr_fd(environment->content, fd);
        }
        else if (environment->is_var)
            ft_putstr_fd("=", fd);
        if (environment->is_var)
            ft_putstr_fd("\n", fd);
        environment = environment->next;
    }
}
