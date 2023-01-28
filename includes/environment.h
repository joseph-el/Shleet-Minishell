/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:36:12 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/28 22:36:02 by aelkhali         ###   ########.fr       */
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

t_env   *new_environment(char *content, char *type);
t_env   *insert_environment(t_env **environment, char *type, char *content);
t_env   *init_environment(char **env);
void    delete_environment(t_env **target_node);
int     size_environment(t_env *head);
int     remove_environment(t_env **environment, char *type);
char    *type_environment(char *_env);
char    *content_environment(char *_env);
char    *get_environment(t_env *environment, char *type);
t_env    *find_environment(t_env *environment, char *type);
void    print_environment(t_env *environment, int fd);
t_env   *last_environment(t_env *head);

#endif