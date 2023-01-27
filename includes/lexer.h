/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:57:21 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/26 16:33:43 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

#include "minishell.h"

# define  UNEXPECTED_TOKEN	     "syntax error near unexpected token "
# define  UNCLOSED_SQ            "unclosed single quotes "
# define  UNCLOSED_DQ	           "unclosed double quotes "
# define  NEWLINE 10
# define  DOLLAR 36
# define  LEFT 1 << 0
# define  RIGHT 1 << 1
# define  COUNTER 1

typedef enum s_token
{
  BEGINOFCMD = 1 << 0,
  ENDOFCMD = 1 << 1,
  WORD = 1 << 2,
  WSPACE = 1 << 3,
  VAR = 1 << 4,
  RECENTEXC = 1 << 5,
  PIPE = 1 << 6,
  GREAT = 1 << 7,
  LESS = 1 << 8,
  SQUOTE = 1 << 9,
  DQUOTE = 1 << 10,
  WILD = 1 << 11,
  LPAR = 1 << 12,
  RPAR = 1 << 13,
  OR = 1 << 14,
  AND = 1 << 15,
  APPEND = 1 << 16,
  HERDOC = 1 << 17,
  CMDEXC = 1 << 18,
  CONNECTOR = (PIPE | OR | AND),
  STRING = (SQUOTE | DQUOTE | WORD | VAR | WILD),
  REDIRECT = (GREAT | LESS | APPEND | HERDOC)
}                     t_token;

typedef struct  s_node
{
    t_token        tok;
    char           *data;
    struct s_node  *next;
    struct s_node  *prev;
}               t_node;

typedef struct s_lexer
{
    int  l_size;
    t_node  *head;
    t_node  *buttom;
}               t_lexer;

typedef t_lexer t_list;


/**
 * @brief * List destroyer
 *          And construct
 */

t_lexer	*lexer(char *cmdline);
t_list	*set_token(char *l_cmd);

char	*handle_state(t_list *l_lexer, char *l_cmd);
char  *parentheses(t_list *l_lexer, char *l_cmd);
char	*normal_stat(t_list *l_lexer, char *l_cmd);
char  *whitespace(t_list *l_lexer, char *l_cmd);
char  *d_quote(t_list *l_lexer, char *l_cmd);
char  *s_quote(t_list *l_lexer, char *l_cmd);
char  *dollar(t_list *l_lexer, char *l_cmd);


bool  g_parentheses(t_node *crr_node, t_node *left, t_node *right, int flag);
bool	connector_syntax(t_node *crr_node);
bool	redirect_syntax(t_node *crr_node);
bool	quote_syntax(t_node *crr_node);
int	  syntax(t_lexer *l_lexer);

// t_list  *expander(t_lexer *l_list);
// t_node  *wildcard(t_node *target);
// bool    match(char *text, char *pattern);
// t_node  *expand(t_list *l_list, t_node *object);
// t_list  *expandcmd(t_list *l_list);

// void    print_lexer(t_exp *node);
void    print_arr(char **arr);
t_list *new_list(void);
t_node  *creat_node(char *data, t_token token);
t_node  *get_node(t_node *crr_node, int mode);
void    push_back(t_lexer **lexer, t_node *n_node);


t_node  *delete_node(t_list *list, t_node *fordelete);
t_node  *delete_front(t_list *list);
t_node  *delete_back(t_list *list);
void    clear_nodes(t_list *list);


#endif