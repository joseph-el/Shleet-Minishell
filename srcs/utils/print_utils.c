/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:32:44 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 18:33:27 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_arr(char **arr)
{
    int len;    
    len = 0;
    if (!arr[0] || !arr)
        return ;
    while (arr && arr[len])
        len ++;
    puts("|-____________________________________________");
    for (size_t i = 0; i < len; i++)
        fprintf(stderr, "===>(CMDEXC) |%s|\n", arr[i]);
    puts("|-____________________________________________\n");
}

void    print_expander(t_expander *l_expander)
{
    t_exp       *exp;
    t_cmdexc    *node;

    exp = l_expander->head;
    if (!exp)
    {
        puts("Error In print");
        return;
    }
    
    while (exp)
    {
        if (exp->nature & NODE_ENDOFCMD)
        {
            fprintf(stderr,YELLOW"\nEND__OF__CMD\n"WHITE);
        }
        if (exp->nature & (NODE_AND | NODE_OR))
        {
            if (exp->nature & NODE_AND)
                fprintf(stderr,GREEN"\nNODE-AND\n"WHITE);
            else
                fprintf(stderr,GREEN"\nNODE-OR\n"WHITE);
        }
        if (exp->grb)
        {
            fprintf(stderr, YELLOW"\nSTART PRINTING GRB NODE\n"WHITE);
            fprintf(stderr, "\n-----------------------\n");
            node = exp->grb->head;
            while (node)
            {
                fprintf(stderr, "FILE -src|%d|-\\___/-dest|%d|-",node->io_src, node->io_dest);
                if (node->cmdexc)
                {
                    puts(RED"\n-|EXC COMMAND|-\n"WHITE);
                    print_arr(node->cmdexc);
                }
                if (node->node_type == NODE_PIPE)
                {
                    puts(RED"\n-|HERE IS A PIPE|-\n"WHITE);
                }
                node = node->next;
            }
        }
        exp = exp->next;
    }
}
