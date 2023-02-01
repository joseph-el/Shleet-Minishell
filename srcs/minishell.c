/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:07:13 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/01 17:14:57 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define Shleet main

t_global g_global = {.gc = NULL,.envp = NULL ,.status = 0,.is_runing = 0};

void init_terminal(void);

void    set_global(char **envp, t_expander **l_expander, t_lexer **l_lexer)
{
    g_global.gc = gc_init();
    if (!g_global.gc)
        return (shleet_error("malloc", strerror(ENOMEM), 1), exit(1));
    g_global.envp = init_environment(envp);
    *l_expander = NULL;
    *l_lexer = NULL;
}

int Shleet(int argc, char **args, char **envp)
{
    t_expander  *l_expander;
    t_lexer     *l_lexer;
    char        *line;

    (void)argc;
    (void)args;
    set_global(envp, &l_expander, &l_lexer);
    system("clear");
    while (true)
    {
        init_terminal();
        line = readline(GREEN "Shleet-Minishell>$ " WHITE);
        if (!line)
            break;
        add_history(line);
        gc_adding_adress(g_global.gc, line, TMP);
        g_global.is_runing = RUNING;
        l_lexer = lexer(line);
        l_expander = expander(l_lexer);
        executor(l_expander);
        g_global.is_runing = BREAKING;
        gc_purifying(&g_global.gc, CLEAN_TMP);
    }
    clean_out();
    return (EXIT_SUCCESS);
}