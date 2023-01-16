/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:51:32 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/17 00:33:53 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_global = {.gc = NULL, .prgrame_name = NULL, .status = 0};

int main(int argc, char **args, char **env)
{
    t_lexer     *l_lexer;
    char        *line;

    if (argc <= 1)
        return (puts("bad args"), EXIT_FAILURE);
    
    g_global.gc = gc_init();
        
    //line = strdup("echo \"This is exit status $? And this is my name $USER OLD $DEXER\" && cat Makefile | grep yoel-idr | wc -l > outfile && rm -drf outfile\n");
    line = strdup("echo \'$DEXER\' || ls -a && ls *");
    
    l_lexer = lexer(line);
    if (!l_lexer)
        return (EXIT_FAILURE);
    


    /*---|print result|---*/
    
    print_lexer(l_lexer->head);
    puts("\n");
    puts(line);
    puts("\nEXIT_SUCCESS\n");

    return (EXIT_SUCCESS);
}