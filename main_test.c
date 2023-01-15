/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 08:49:29 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/15 17:29:10 by yoel-idr         ###   ########.fr       */
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


typedef enum s_enum
{
    PIPE = '|',
    SQUT = '<',
    DQUT = '>',

    LL = '<' * 2,
    LLS = '>' * 2,
    
    CO = (SQUT | DQUT | LL | LLS)
    
}           t_tok;


int main()
{

    int ii = '>>';
    

    printf("test |%c|\n", ii);
    // int mode = FORK | INPUT;

    // if (mode & OUTPUT)
    //     puts("hey");
    // else
    //     puts("NOn");

}