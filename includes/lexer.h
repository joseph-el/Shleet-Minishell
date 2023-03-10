/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:46:35 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/14 18:33:21 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define UNEXPECTED_TOKEN "syntax error near unexpected token "
# define UNCLOSED_SQ "unclosed single quotes "
# define UNCLOSED_DQ "unclosed double quotes "
# define NEW_LINE 10
# define DOLLAR 36
# define LEFT 1
# define RIGHT 2
# define COUNTER 4

typedef enum s_token
{
	BEGINOFCMD = 2 << 0,
	ENDOFCMD = 2 << 1,
	WORD = 2 << 2,
	WSPACE = 2 << 3,
	VAR = 2 << 4,
	PIPE = 2 << 5,
	GREAT = 2 << 6,
	LESS = 2 << 7,
	SQUOTE = 2 << 8,
	DQUOTE = 2 << 9,
	WILD = 2 << 10,
	LPAR = 2 << 11,
	RPAR = 2 << 12,
	OR = 2 << 13,
	AND = 2 << 14,
	APPEND = 2 << 15,
	HERDOC = 2 << 16,
	CONNECTOR = (PIPE | OR | AND),
	STRING = (SQUOTE | DQUOTE | WORD | VAR | WILD),
	REDIRECT = (GREAT | LESS | APPEND | HERDOC)
}					t_token;

typedef struct s_node
{
	t_token			tok;
	char			*data;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_lexer
{
	int				l_size;
	t_node			*head;
	t_node			*buttom;
}					t_lexer;

typedef t_lexer		t_list;

t_lexer				*lexer(char *cmdline);
t_list				*set_token(char *l_cmd);
int					syntax(t_lexer *l_lexer);

char				*parentheses(t_list *l_lexer, char *l_cmd);
char				*d_quote(t_list *l_lexer, char *l_cmd);
char				*s_quote(t_list *l_lexer, char *l_cmd);
char				*dollar(t_list *l_lexer, char *l_cmd);
int					bare_quotes(t_lexer *l_lexer, char *l_cmd);

char				*handle_state(t_list *l_lexer, char *l_cmd);
char				*normal_stat(t_list *l_lexer, char *l_cmd);
char				*is_whitespace(t_list *l_lexer, char *l_cmd);

t_list				*new_list(void);
t_node				*creat_node(char *data, t_token token);
t_node				*get_node(t_node *crr_node, int mode);
void				push_back(t_lexer **lexer, t_node *n_node);

t_node				*delete_front(t_list *list);
t_node				*delete_back(t_list *list);
t_node				*delete_node(t_list *list, t_node *fordelete);

bool				g_parentheses(t_node *crr_node, t_node *left, t_node *right,
						int flag);
bool				connector_syntax(t_node *crr_node);
bool				redirect_syntax(t_node *crr_node);
bool				quote_syntax(t_node *crr_node);

#endif
