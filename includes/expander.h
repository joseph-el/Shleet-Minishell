/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:49:40 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/30 16:29:07 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

# define FILE_PERM 0664
# define WIRITE_ 0
# define READ_ 1

typedef enum s_node_type
{
    NODE_CMDEXC = 1 << 0,
    NODE_PIPE = 1 << 1,
    NODE_AND  = 1 << 2,
    NODE_OR   = 1 << 3,
    NODE_ENDOFCMD = 1 << 4
}               t_type;


typedef struct s_cmdexc
{
    int             io_src;
    int             io_dest;
    char            **cmdexc;
    t_type          node_type;
    struct s_cmdexc *next;
    struct s_cmdexc *prev;

}               t_cmdexc;

typedef struct s_grb
{
    bool            is_executed;
    t_cmdexc        *head;
    t_cmdexc        *tail; 
}               t_grb;

typedef struct s_exp
{
    t_type              nature;
    t_grb               *grb;
    struct s_exp        *prev;
    struct s_exp        *next;
}               t_exp;


typedef struct s_expander
{
    t_exp   *head;
    t_exp   *tail;
}               t_expander;

/**
 * @brief expanding all
 * 
 * @param l_lexer 
 * @return t_expander* 
 */

t_expander	*expander(t_lexer *l_lexer);

/**
 * @brief list construct.c
 * 
 * @return t_grb t_expander t_exp t_cmdexc
 */

t_expander  *new_explist(void);
t_cmdexc    *new_cmdexc(char **target, t_type nature);
t_grb       *new_grb(void);
t_exp       *new_exp(t_type nature);
void        add_back(t_expander **expander, t_exp *n_exp);
void        add_cmdexc_back(t_grb **grb, t_cmdexc *new_cmdexc);


/**
 * @brief expansion
 * @return t_lexer
 */

t_node  *fill_content(t_list *l_list, t_node *object);
t_lexer  *list_expansion(t_lexer *l_list);
t_list  *quotes_removal(t_list *e_list);

/**
 * @brief test Toolss
 * @return int char **
 */

int     herdoc(char *limiter, int *fds);
char	**realloc_array(char **array, char *new);
t_node  *wildcard(t_node *target);


#endif