/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:37:34 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/27 19:40:00 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int set_rederct(int *io_infile, int *io_outfile, char *filename, t_token token)
{
    int o_flag;
    int *fds;

    o_flag = O_RDONLY;
    if (token & (APPEND | GREAT))
    {
        if (token & APPEND)
            o_flag = O_CREAT | O_RDWR | O_APPEND;
        else
            o_flag = O_CREAT | O_RDWR | O_TRUNC;
        return (*io_outfile = open(filename, o_flag, FILE_PERM));
    }
    if (token & LESS)
        return (*io_infile = open(filename, o_flag, FILE_PERM));
    fds = gc(g_global.gc, malloc(sizeof(int) * 2), TMP);
    if (!fds || herdoc(filename, fds) < 0)
        return (-1);
    return (*io_infile = fds[0]);
}

char    **realloc_array(char **array, char *new)
{
    char    **ret;
    int         i;

    i = -1;
    if (!array)
    {
        ret = malloc(sizeof(char *) * 2);
        return (ret[0] = ft_strdup(new), ret[1] = 0x0, ret);
    }
    while (array[++i])
        ;
    ret = malloc(sizeof(char *) * (i + 2));
    if (!ret)
        return (NULL);
    i = -1;
    while (array[++i])
        ret[i] = ft_strdup(array[i]);
    ret[i++] = ft_strdup(new);
    ret[i] = NULL;
    i = -1;
    while (array[++i])
        free(array[i]);
    free(array);
    return (ret);
}

t_exp   *expand(t_node **object, int flag, t_type nature)
{
    t_exp   *n_node;
    char    **cmdexc;

    n_node = new_exp(nature);
    if (!n_node || (*object)->tok & ENDOFCMD)
        return (n_node->node_type = NODE_ENDOFCMD, n_node);
    cmdexc = NULL;
    while ((*object) && (*object)->tok & flag)
    {
        if ((*object)->tok & (WORD | VAR | WILD) && (*object)->prev->tok & ~REDIRECT)
            cmdexc = realloc_array(cmdexc, (*object)->data);
        
        if ((*object)->tok & REDIRECT)
            set_rederct(&n_node->io_inf, &n_node->io_out, (*object)->next->data, (*object)->tok);
        
        if ((*object)->tok & CONNECTOR)
            n_node->connector = new_connector(NULL, NULL, (*object)->tok);
        
        (*object) = (*object)->next;
    }
    if (flag & (WILD | VAR | WORD | REDIRECT))
        n_node->cmdexc = cmdexc; // leaks on malloc(2) in split
    return (n_node);
}

t_expander  *set_connections(t_expander *l_expander)
{
    t_exp   *head;

    head = l_expander->head;
    while (head)
    {
        if (head->node_type & (NODE_AND | NODE_OR | NODE_PIPE))
        {
            head->connector->left = head->prev;
            head->connector->right = head->next;
        }
        head = head->next;
    }
    return (l_expander);
}

int set_expand(t_expander *l_expander, t_lexer *l_lexer)
{
    t_node  *head;
    t_type  nature;

    l_lexer = quotes_removal(l_lexer);
    l_lexer = list_expansion(l_lexer);
    head = l_lexer->head;
    if (!head || head->tok & ENDOFCMD)
        return (EXIT_FAILURE);
    while (head)
    {
        if (head->tok & (REDIRECT | STRING))
            add_back(&l_expander, expand(&head, REDIRECT | STRING, NODE_CMDEXC));
        else if (head->tok & CONNECTOR)
        {
            nature = (head->tok == PIPE) * NODE_PIPE + (head->tok == OR) * NODE_OR + (head->tok == AND) * NODE_AND;
            add_back(&l_expander, expand(&head, CONNECTOR, nature));
        }
        else
            head = head->next;
    }
    l_expander = set_connections(l_expander);
    return (EXIT_SUCCESS);
}

t_expander  *expander(t_lexer *l_lexer)
{
    t_expander  *l_expander;
    int         status;
    
    l_expander = new_explist();
    if (!l_expander)
        return (NULL);
    status = set_expand(l_expander, l_lexer);
    if (status)
    {
        shleet_error("expander", "syntax error", 2);
        return (NULL);
    }
    return (l_expander);
}