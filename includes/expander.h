/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:52:00 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/27 19:16:11 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# define FILE_PERM 0664
# define WIRITE_ 0
# define READ_ 1

# include "minishell.h"

typedef enum s_node_type
{
    NODE_CMDEXC = 1 << 0,
    NODE_PIPE = 1 << 1,
    NODE_AND  = 1 << 2,
    NODE_OR   = 1 << 3,
    NODE_ENDOFCMD = 1 << 4
}               t_type;

typedef struct s_connector
{
    t_token         type;
    struct  s_exp   *left;
    struct  s_exp   *right;
}               t_connector;

typedef struct s_exp
{
    int                 io_inf;
    int                 io_out;
    char                **cmdexc;
    t_connector         *connector;
    t_type              node_type;
    struct s_exp        *prev;
    struct s_exp        *next;
}               t_exp;

typedef struct s_expander
{
    t_exp   *head;
    t_exp   *tail;
}               t_expander;

t_expander  *expander(t_lexer *l_lexer);

t_connector *new_connector(t_exp *left, t_exp *right, t_token type);
t_expander  *new_explist(void);
t_lexer     *list_expansion(t_lexer *l_list);
t_node      *fill_content(t_list *l_list, t_node *object);
t_node      *wildcard(t_node *target);
t_list      *quotes_removal(t_list *e_list);
t_exp       *new_exp(t_type node_type);
void        add_back(t_expander **expander, t_exp *n_node);
int         herdoc(char *limiter, int *fds);





#endif
