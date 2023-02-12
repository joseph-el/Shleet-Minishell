/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:36:12 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/29 18:29:24 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

# include "minishell.h"
# define place_holder "declare -x "

typedef struct s_env
{
    char            *content;
    char            *type;
    int             is_var;
	struct s_env	*prev;
    struct s_env    *next;
}               t_env;

t_env   *new_environment(char *content, char *type);
t_env   *insert_environment(t_env **environment, char *type, char *content, char *env);
t_env   *init_environment(char **env);
t_env   *last_environment(t_env *head);
t_env   *find_environment(t_env *environment, char *type);
char    *type_environment(char *_env);
char    *content_environment(char *_env);
char    **export_to_array(t_env *head);
char    *get_environment(t_env *environment, char *type);
void    delete_environment(t_env **target_node);
void	print_exp_env(t_env *node, int fd);
void    print_environment(t_env *environment, int fd);
int     remove_environment(t_env **environment, char *type);
int     size_environment(t_env *head);

#endif