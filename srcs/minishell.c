/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:07:13 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/03 22:43:31 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int *save_io(void)
{
    int *save;

    save = gc(g_global.gc, malloc(sizeof(int) * 2), TMP);
    if (!save)
        return (NULL);
    save[0] = dup(0);
    save[1] = dup(1);
    return (save);
}

void    rest_io(int *fds)
{
    dup2(fds[0], 0);
    dup2(fds[1], 1);  
}

int main(int argc, char **args, char **envp)
{
    t_expander  *l_expander;
    t_lexer     *l_lexer;
    char        *line;
    int *fds;

    (void)argc;
    (void)args;
    set_global(envp, &l_expander, &l_lexer);
    system("clear");
    while (true)
    {
        init_terminal();
        fds = save_io();
        line = readline(GREEN "Shleet-Minishell>$ " WHITE);
        if (!line)
        {
            fprintf(stdin, "Iam in break\n");
            break;
        }
        add_history(line);
        gc_adding_adress(g_global.gc, line, TMP);
        l_lexer = lexer(line);
        l_expander = expander(l_lexer);
        executor(l_expander);
        rest_io(fds);
        gc_purifying(&g_global.gc, CLEAN_TMP);
    }
    clean_out();
    return (EXIT_SUCCESS);
}