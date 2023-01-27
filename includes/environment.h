/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:36:12 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/25 10:53:34 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "minishell.h"

typedef struct s_env
{
    char            *content;
    char            *type;
	struct s_env	*prev;
    struct s_env    *next;
}               t_env;

#endif