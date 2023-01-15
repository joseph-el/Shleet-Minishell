/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:04:19 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/15 22:14:25 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <paths.h>
# include <limits.h>
#include <string.h>

#include "../../libgc/include/gc.h"

# define UNEXPECTED_TOKEN	"syntax error near unexpected token"
# define UNEXPECTED_EOF     "unexpected EOF while looking for matching"
# define UNCLOSED_SQ        "unclosed single quotes"
# define UNCLOSED_DQ	    "unclosed double quotes"

# define FAILURE 1 << 1
# define SUCCESS 1 << 0

# define ADD_BACK 1
# define ADD_FRONT 2
# define INSERT_NODE 3

typedef short int lexer_flag;

typedef enum s_token
{
    BEGINOFCMD = 1,
    ENDOFCMD = 2,
    WORD = 3,
    WSPACE = 4,
    VAR = 5,
    RE  =  6,
    
    NEWLINE = '\n',
    PIPE = '|',
    GREAT = '>',
    LESS = '<',
    DOLLAR = '$',
    BG = '&',
	  SQUOTE = '\'',
	  DQUOTE = '\"',
    WILD = '*',

    AND = (BG * 2),
    OR = (PIPE * 2),
    IOGREAT = (GREAT * 2),
    IOLESS = (LESS * 2),
    
    REDIRECT = (GREAT | LESS),
    STRING = (SQUOTE | DQUOTE),

}                   t_token;

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


/*global struct*/

typedef struct s_global
{
    t_gc    *gc;
    char    *prgrame_name;
    short   status;
}               t_global;

extern t_global g_global;


/* ------------- Lexer help functions -------------------- */

  /*Handle whitwspace*/
  
void    whitespace(t_lexer *lexer, char **cmdline);

  /*Handle single quote*/

void    s_quote(t_lexer *lexer, char **cmdline);

  /*Handle dollar*/

void    dollar(t_lexer  *lexer, char **cmdline);

  /*Handle double quote*/
    
void    d_quote(t_lexer *lexer, char **cmdline);


/*Linked List*/

t_lexer *new_lexer(void);
t_node *creat_node(char *data, t_token token);
void    push_back(t_lexer **lexer, t_node *n_node);
void print_list(t_node *node);
// int    management_list(t_lexer **lexer, t_node *new, t_node *prev, lexer_flag flag);
// int insert_node(t_lexer **lexer, t_node *new, t_node *prev);





/*
------------------------------------------------------------------------------------------------------
*/




/*
-----> Libft function
*/

void	ft_putstr_fd(char *s, int fd);

char	*ft_strchr(const char *str, int c);

int     ft_isspace(int c);

int     ft_isalnum(int c);

int     ft_isdigit(int c);

char    *ft_strndup(char *src, int len);

char    *ft_chardup(char src);


#endif
