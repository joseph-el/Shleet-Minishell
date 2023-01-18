/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:00:18 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/17 20:24:49 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define  UNEXPECTED_TOKEN	  "syntax error near unexpected token "
# define  UNEXPECTED_EOF      "unexpected EOF while looking for matching "
# define  UNCLOSED_SQ         "unclosed single quotes "
# define  UNCLOSED_DQ	        "unclosed double quotes "
# define  RIGHT 4
# define  LEFT 1
# define NEWLINE 10
# define DOLLAR 36

typedef short int lexer_flag;

// typedef enum s_token
// {
//   BEGINOFCMD = 0,
//   ENDOFCMD = 1,
//   WORD = 3,
//   WSPACE = 4,
//   VAR = 5,
//   RECENTEXC = 6,
//   GROUP = 7,
//   NEWLINE = 10,
//   PIPE = 124,
//   GREAT = 62,
//   LESS = 60,
//   DOLLAR = 36,
//   SAND = 38,
//   SQUOTE = 39,
//   DQUOTE = 34,
//   WILD = 42,
//   LPAR = 40,
//   RPAR = 41,
//   AND = (SAND * 2),
//   OR = (PIPE * 2),
//   REGREAT = (GREAT * 2) + 1,
//   RELESS = (LESS * 2)
// }             t_token;

typedef enum s_token
{
  BEGINOFCMD = 1 << 0,
  ENDOFCMD = 1 << 1,
  WORD = 1 << 2,
  WSPACE = 1 << 3,
  VAR = 1 << 4,
  RECENTEXC = 1 << 5,
  GROUP = 1 << 6,
  PIPE = 1 << 7,
  GREAT = 1 << 8,
  LESS = 1 << 9,
  SQUOTE = 1 << 10,
  DQUOTE = 1 << 11,
  WILD = 1 << 12,
  LPAR = 1 << 13,
  RPAR = 1 << 14,
  OR = 1 << 15,
  AND = 1 << 16,
  REGREAT = 1 << 17,
  RELESS = 1 << 18,
  CONNECTOR = (PIPE | OR | AND),
  STRING = (SQUOTE | DQUOTE | WORD | VAR | GROUP),
  REDIRECT = (GREAT | LESS | REGREAT | RELESS)
}                     t_token;

typedef struct s_grb
{
  char          *data;
  t_token       tok;
  struct s_grb  *next;
  struct s_grb  *prev;
}             t_grb;

typedef struct  s_node
{
    char           *data;
    t_token        tok;
    t_grb          *grb;
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