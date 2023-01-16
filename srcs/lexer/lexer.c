/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:05:16 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/16 09:26:51 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexer.h"

/* Use The global var for @garbage*/

t_global g_global = {.gc = NULL, .prgrame_name = NULL, .status = 0};

/*Handle | << >> < > && || */

void    handle_state(t_lexer *lexer, char **cmdline)
{
    int *target;
    t_token tok1;
    t_token tok2;
    t_token type;
    
    target = gc_filter(g_global.gc, malloc(sizeof(int) * 2));
    if (! target)
        return ;
    target[0] = (*cmdline)[0];
    target[1] = (*cmdline)[1];
    
    tok1 = (*target == PIPE) * PIPE + (*target == GREAT) * GREAT + (*target == LESS) * LESS + (*target == SAND) * SAND;
    tok2 = (*(target + 1) == GREAT) * GREAT + (*(target + 1) == LESS) * LESS + (*(target + 1) == PIPE) * PIPE + (*(target + 1) == SAND) * SAND;
    type = ((tok1 + tok2) == REGREAT) * REGREAT + ((tok1 + tok2) == RELESS) * RELESS + ((tok1 + tok2) == AND) * AND + ((tok1 + tok2) == OR) * OR;
    
    if (tok1 && tok2)
    {
        push_back(&lexer, creat_node(ft_strndup(*cmdline, 2), type));
        (*cmdline) += 2;
    }
    else
    {
        push_back(&lexer, creat_node(ft_strndup(*cmdline, 1), tok1));
        (*cmdline) += 1;
    }
}

/* Handle normal state and Wildcard (*) */

void    state_normal(t_lexer *lexer, char **cmdline)
{
    bool    state;
    int     len;

    len = 0;
    state = false;
    while ((*cmdline)[len] && !ft_strchr("|<>&", (*cmdline)[len]) && !ft_isspace((*cmdline)[len]))
    {
        if ((*cmdline)[len] == WILD)
            state = true; 
        len ++;
    }
    if (!state)
        push_back(&lexer, creat_node(ft_strndup(*cmdline, len), WORD));
    else
        push_back(&lexer, creat_node(ft_strndup(*cmdline, len), WILD));
    (*cmdline) += len;
}

/* the tokenizer */

t_lexer *set_token(char *cmdline)
{
    t_lexer *l_lexer;

    l_lexer = new_lexer();
    if (!l_lexer)
        return (NULL);
        
    push_back(&l_lexer, creat_node(NULL, BEGINOFCMD));
    
    while (*cmdline && *cmdline != NEWLINE)
    {
        if (ft_isspace(*cmdline))
        {
            whitespace(l_lexer, &cmdline);
        }
        else if (*cmdline == SQUOTE)
        {            
            s_quote(l_lexer, &cmdline);

        }
        else if (*cmdline == DQUOTE)
        {
            d_quote(l_lexer, &cmdline);
        }
        else if (*cmdline == DOLLAR)
        {            
            dollar(l_lexer, &cmdline);
        }
        else if (ft_strchr("|<>&", *cmdline))
        {            
            handle_state(l_lexer, &cmdline);
        }
        else
        {
            state_normal(l_lexer, &cmdline);
        }
    }
    
    push_back(&l_lexer, creat_node(NULL, ENDOFCMD));
    return (l_lexer);
}









/*demo lexer*/

t_lexer *lexer(char *cmdline)
{
    t_lexer *l_lexer;

    l_lexer = set_token(cmdline);
    if (!l_lexer)
        return (NULL);
    return (l_lexer);   
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
    char    *ptr;
	int		lenght;

	if (!s1 || !s2)
		return (NULL);
	lenght = strlen(s1) + strlen(s2);
	str = malloc(sizeof(char) * (lenght + 1));
	if (!str)
		return (NULL);
    ptr = str;
	memmove(str, s1, strlen(s1));
	memmove(str + strlen(s1), s2, strlen(s2));
	return (ptr);
}

/* Main for test the Lexer */

// ls -a << 'test' || ls -a && gcc -a && yoel-idr | cat -e > outfile | grep user | wc -l >> outfile 

int main(int ac, char **av)
{
    t_lexer *test;
    char *line;

    if (ac <= 1)
        return (puts("bad args"), EXIT_FAILURE);
        
    g_global.gc = gc_init();
    line = ft_strjoin(av[1], "\n");

    test = lexer(line);
    
    if (!test)
        return (puts("NULL ADDRESS"), EXIT_FAILURE);
    
    /*print list of lexer*/
    
    print_list(test->head);
    
    // affiche cmd
    puts("");
    puts(line);
    
    puts("\nEXIT_SUCCESS\n");
    
    return (EXIT_SUCCESS);
}