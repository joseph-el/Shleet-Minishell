/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:51:32 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/18 01:04:17 by yoel-idr         ###   ########.fr       */
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
        
    //line = ft_strdup("echo \"This is exit status $USER And this is my name $USER OLD $DEXER\" && cat Makefile | grep yoel-idr | wc -l > outfile && rm -drf outfile\n");
    line = ft_strdup("echo (\"hhhhhhhhh\")");

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