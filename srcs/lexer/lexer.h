/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:36:15 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/12 16:59:35 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# define UNCLOSED_SQ	"Unclosed single quotes"
# define UNCLOSED_DQ	"Unclosed double quotes"
#define N_FRONT 1
#define N_BACK  4
#define N_PALCE 8

typedef enum s_enum
{
    CMDBEGIN = 1 << 0,
    LASTCMD = 1 << 1,
    PIPE = '|',
    AND  = '&',
    SQUOTE = '\'',
    DQUOTE = '"',
    DOLLAR = '$',
    LESS = '<',
    GREAT = '>',
	CONNECTOR = (AND | PIPE),
    STRING = (DQUOTE | SQUOTE)
}           t_token;

typedef struct s_list
{
    char        *data;
    t_token     token;
    struct s_list *next;
    struct s_list *prev;
}					t_list;

typedef struct s_adress
{
    t_list  *next;
    t_list  *prev;
}               t_adress;


#endif