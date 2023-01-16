/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:00:18 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/17 00:52:15 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define  UNEXPECTED_TOKEN	  "syntax error near unexpected token\n"
# define  UNEXPECTED_EOF      "unexpected EOF while looking for matching\n"
# define  UNCLOSED_SQ         "unclosed single quotes\n"
# define  UNCLOSED_DQ	        "unclosed double quotes\n"
# define  RIGHT 4
# define  LEFT 1

typedef short int lexer_flag;

typedef enum s_token
{
  BEGINOFCMD = 0,
  ENDOFCMD = 1,
  WORD = 3,
  WSPACE = 4,
  VAR = 5,
  RECENTEXC = 6,
  NEWLINE = 10,
  PIPE = 124,
  GREAT = 62,
  LESS = 60,
  DOLLAR = 36,
  SAND = 38,
  SQUOTE = 39,
  DQUOTE = 34,
  WILD = 42,
  AND = (SAND * 2),
  OR = (PIPE * 2),
  REGREAT = (GREAT * 2) + 1,
  RELESS = (LESS * 2)
}             t_token;

typedef struct  s_node
{
    char    *data;
    t_token tok;
    struct s_node  *next;
    struct s_node  *prev;
}               t_node;

typedef struct s_lexer
{
    size_t  l_size;
    t_node  *head;
    t_node  *buttom;
}               t_lexer;

typedef t_lexer t_list;

/*-------- lexer Utils ---------*/

t_lexer *lexer(char *cmdline);
t_list  *set_token(char *l_cmd);
char    *handle_state(t_list *l_lexter, char *l_cmd);
char    *whitespace(t_list *l_lexer, char *l_cmd);
char    *s_quote(t_list *l_lexer, char *l_cmd);
char    *dollar(t_list  *l_lexer, char *l_cmd);
char    *d_quote(t_list *l_lexer, char *l_cmd);
char    *normal_stat(t_list *l_lexer, char *l_cmd);

/*-------- Syntax Utils ---------*/

int     syntax(t_lexer *l_lexer);
bool    connector_syntax(t_node *crr_node);
bool    redirect_syntax(t_node  *crr_node);
bool    search(t_node *current, t_token tok);
bool    quote_syntax(t_node *crr_node, int *remember);

#endif