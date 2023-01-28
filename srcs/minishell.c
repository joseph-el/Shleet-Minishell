/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:08:04 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/28 22:47:12 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

t_global g_global = {.gc = NULL,.envp = NULL ,.status = 0};

// void    print_arr(char **arr)
// {
//     int len;    
//     len = 0;
//     if (!arr[0] || !arr)
//         return ;
//     while (arr && arr[len])
//         len ++;
//     puts("|-____________________________________________");
//     for (size_t i = 0; i < len; i++)
//         fprintf(stderr, "===>(CMDEXC) |%s|\n", arr[i]);
//     puts("|-____________________________________________\n");
// }

// void    print_lexer(t_exp *node)
// {
//     if (!node)
//     {
//         puts("Error in print_list");
//         return ;        
//     }
//     while (node)
//     {
//         // fprintf(stderr, "SHOWING -|%d|==================>/\\ \n\n", node->node_type);
//         if (node->node_type == NODE_CMDEXC)
//         {
//             puts("EXC CMD\n");
//             print_arr(node->cmdexc);
//             fprintf(stderr, "|-------------check fds oi_|%d| io_|%d|-------------|\n", node->io_inf, node->io_out);
//         }
//         if (node->node_type == NODE_AND)
//         {
//             //fprintf(stderr, "-------- check right |%s| and left |%s|-----------\n", node->connector->right, node->connector->left.);
//             puts("NODE_AND\n");
//         }
//         if (node->node_type == NODE_OR)
//         {
//             puts("NODE_OR\n");
//         }
//         if (node->node_type == NODE_PIPE)
//         {
//             puts("NODE_PIPE\n");
//         }
//         node = node->next;
//     }
// }


int main(int argc, char **args, char **env)
{
    t_lexer     *l_lexer = NULL;
    t_expander  *exp = NULL;
    char        *line;
    
    if (argc <= 1)
        return (perror(""), EXIT_FAILURE);
    g_global.gc = gc_init();
    system("clear");
    while (true)
    {
        line = readline(GREEN"Shleet-Minishell>$ "WHITE);
        gc_adding_adress(g_global.gc, line, TMP);
        add_history(line);
        if (!ft_memcmp(line, "stop", sizeof("stop")))
            break;
        l_lexer = lexer(line);
        exp = expander(l_lexer);

        //print_lexer(exp->head);

        if (!l_lexer)
            continue;
        puts("\n");
        puts(line);
        puts("\nEXIT_SUCCESS\n");
        if (!ft_memcmp(line, "clear", sizeof("clear")))
                system("clear");
        gc_purifying(g_global.gc, TMP);
    }
    
    /*---|print result|---*/
        // print_lexer(l_lexer->head);
        gc_purifying(g_global.gc, ALL);
        free(g_global.gc);
        system("leaks lexer");
    return (EXIT_SUCCESS);
}