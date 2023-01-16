/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 08:49:29 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/16 12:24:19 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define c 1
#define v 4
#define k 8


# define OUTPUT 1
# define INPUT 2
# define FORK 3
# define PROCESS 4

typedef enum s_test
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
  REGREAT = (GREAT * 2),
  RELESS = (LESS * 2),
  
  REDIRECT = (GREAT | LESS | REGREAT | RELESS),
  
  CONNECTOR = (AND | PIPE | OR),
  
  STRING = (WORD | SQUOTE | DQUOTE | WILD)
  
  
}             t_test;

// typedef enum e_token
// {

    
// 	CMDBEGIN = 1 << 0,
// 	ENDOFCMD = 1 << 1,
// 	WSPACE = 1 << 2,
// 	WORD = 1 << 3,
// 	PIPE = 1 << 4,
// 	AND = 1 << 5,
// 	OR = 1 << 6,
// 	OPAR = 1 << 7,
// 	CPAR = 1 << 8,
// 	BG = 1 << 9,
// 	FG = 1 << 10,
// 	DSEMI = 1 << 11,
// 	VAR = 1 << 12,
// 	TILDE = 1 << 13,
// 	WILDC = 1 << 14,
// 	SQUOTE = 1 << 15,
// 	DQUOTE = 1 << 16,
// 	LESS = 1 << 17,
// 	DLESS = 1 << 18,
// 	GREAT = 1 << 19,
// 	DGREAT = 1 << 20,
// 	GROUP = 1 << 21,
// 	STRING = (GROUP | WORD | TILDE | WILDC | VAR | SQUOTE | DQUOTE),
// 	REDIRECT = (LESS | DLESS | GREAT | DGREAT),
// 	CONNECTOR = (AND | OR | PIPE | FG | BG)

// }	t_token;
// typedef enum s_enum
// {
//     PIPE = '|',
//     SQUT = '<',
//     DQUT = '>',

//     LL = '<' * 2,
//     LLS = '>' * 2,
    
//     CO = (SQUT | DQUT | LL | LLS)
    
// }           t_tok;


int main()
{
    int mode = AND & CONNECTOR;


    unsigned int ttt;

    ttt = PIPE << 1;

    printf("check 11 ttt |%d|\n", ttt);
    
    ttt >>= 1;

    printf("check 22 ttt |%c|\n", ttt);


    open(O_CREAT | O)
    tok 

    if (tok == and || tok )

    if (tok & conct)
    // printf("afff Mode |%d|\n", mode);
    
    // if (!mode)
    //     puts("yes");
    // else 
    //     puts("NO");
    
    //printf("check connct |%d|\n", GREAT);


    // int mode = FORK | INPUT;

    // if (mode & OUTPUT)
    //     puts("hey");
    // else
    //     puts("NOn");

}