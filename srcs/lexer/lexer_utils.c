/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:05:02 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/16 09:26:32 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*Linked list tools*/

t_lexer *new_lexer(void)
{
    t_lexer *lexer;

    lexer = gc_filter(g_global.gc, malloc(sizeof(t_lexer)));
    if (! lexer)
        return (NULL);
    lexer->buttom = lexer->head = NULL;
    lexer->l_size = 0;
    return (lexer);
}

t_node *creat_node(char *data, t_token token)
{
    t_node  *n_node;

    n_node = gc_filter(g_global.gc, malloc(sizeof(t_node)));
    if (!n_node)
        return (NULL);
    n_node->data = data;
    n_node->next = n_node->prev = NULL;
    n_node->tok = token;
    return (n_node);
}

void    push_back(t_lexer **lexer, t_node *n_node)
{
    if (!(*lexer)->head)
        (*lexer)->head = n_node;
    else
    {
        (*lexer)->buttom->next = n_node;
        n_node->prev = (*lexer)->buttom;
    }
    (*lexer)->buttom = n_node;
    (*lexer)->l_size++;
}

void print_list(t_node *node)
{
    int i;

    i = 1;
    if (!node)
        puts("ERROR IN PRINT_LIST");
    while(node)
    {
        printf("AFFICHE node |%d| type >>(%c)<< -> >>(%s)<<\n\n",i, (char)node->tok, node->data);
        i ++;
        node = node->next;
    }   
}

/*
------------------------------------------------------------------------------------------------------
*/



/* ------------- Lexer help functions -------------------- */

  /*Handle whitwspace*/
  
void    whitespace(t_lexer *lexer, char **cmdline)
{
    int len;

    len = 0;
    while ((*cmdline)[len] && ft_isspace((*cmdline)[len]))
        len ++; 
    if (len)
        push_back(&lexer, creat_node(NULL, WSPACE));
    (*cmdline) += len; 
}
 
  /*Handle single quote*/

void    s_quote(t_lexer *lexer, char **cmdline)
{
    int len;
    
    push_back(&lexer, creat_node(ft_strndup(*cmdline, 1), SQUOTE));
    (*cmdline) += 1;
    len = 0;
    while ((*cmdline)[len] && (*cmdline)[len] != '\n' && (*cmdline)[len] != SQUOTE)
        len ++;
    push_back(&lexer, creat_node(ft_strndup(*cmdline, len), WORD));
    if ((*cmdline)[len] == SQUOTE)
    {
        push_back(&lexer, creat_node(ft_strndup((*cmdline) + len, 1), SQUOTE));
        len ++;
    }
    (*cmdline) += len;
}

  /*Handle dollar*/

void    dollar(t_lexer  *lexer, char **cmdline)
{
    int len;

    if (*(cmdline)[1] == '?')
    {
        push_back(&lexer, creat_node(ft_strndup(*cmdline, 2), RECENTEXC));
        (*cmdline) += 2;
        return ;
    }
    len = 0;
    while ((*cmdline)[len] && (*cmdline)[len] != '\n' && ft_isalnum((*cmdline)[len]))
        len ++;
    if (len)
        push_back(&lexer, creat_node(ft_strndup((*cmdline), len), VAR));
    (*cmdline) += len;
}

  /*Handle double quote*/
    
void    d_quote(t_lexer *lexer, char **cmdline)
{
    bool    mode;
    int     len;
    
    mode = false;
    len = 0;
    (*cmdline) += 1;
    if ((*cmdline)[0] == DQUOTE)
        mode = true;
    push_back(&lexer, creat_node(ft_strndup(*cmdline, 1), DQUOTE));
    while ((*cmdline)[len] && (*cmdline)[len] != '\n' && (*cmdline)[len] != DQUOTE && !mode)
    {
        if ((*cmdline)[len] == DOLLAR)
        {
            if (len)
                push_back(&lexer, creat_node(ft_strndup(*cmdline, len), WORD));
            dollar(lexer, &(*cmdline) + len);
            len = 0;
        }
        else
            len ++;
    }
    if (len && !mode)
        push_back(&lexer, creat_node(ft_strndup(*cmdline, len), WORD));
    if (mode)
        push_back(&lexer, creat_node(ft_strdup(""), WORD));
    if ((*cmdline)[len] == DQUOTE || mode)
        push_back(&lexer, creat_node(ft_strndup(*cmdline, 1), DQUOTE));
    (*cmdline) += len;
}


/*
------------------------------------------------------------------------------------------------------
*/

/*
-----> Libft function
*/

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
	}
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str && *str != (char)c)
		str++;
	if (*str == '\0' && *str != (char)c)
		return (NULL);
	return ((char *)str);
}

int     ft_isspace(int c)
{
    return (c == 32 || (c >= 9 && c <= 13));
}

int     ft_isalnum(int c)
{
	return (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= '0' && c <= '9');
}

int     ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

char    *ft_strndup(char *src, int len)
{
    char    *dest;

    dest = gc_filter(g_global.gc, malloc(len + 1));
    if (!dest)
        return (NULL);
    strlcpy(dest, src, len + 1);
    return (dest);
}

char    *ft_chardup(char src)
{
    char *dest;
    
    dest = gc_filter(g_global.gc, malloc(2));
    if (!dest)
        return (NULL);
    *dest = src;
    *(dest + 1) = 0;
    return (dest);
}

char	*ft_strdup(char *s1)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = gc_filter(g_global.gc, malloc(sizeof(char) * (strlen(s1) + 1)));
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}



/*FOR another Time*/


// int    management_list(t_lexer **lexer, t_node *new, t_node *prev, lexer_flag flag)
// {
//     if (flag & ADD_BACK)
//     {
//         if (!(*lexer))
//             (*lexer)->head = new;
//         else
//         {
//             new->prev = (*lexer)->buttom;
//             (*lexer)->buttom->next = new;            
//         }
//         (*lexer)->buttom = new;
//         (*lexer)->l_size ++;
//     }
//     else if (flag & ADD_FRONT)
//     {
//         if (!(*lexer))
//             (*lexer)->head = new;
//         else
//         {
//             new->next = (*lexer)->head;
//             (*lexer)->head->prev = new;
//             (*lexer) = new;        
//         }
//         (*lexer)->l_size ++;
//     }
//     else if (flag & INSERT_NODE)
//         if (!insert_node(lexer, new, prev));
//             return (FAILURE);
//     return (SUCCESS);
// }

// int insert_node(t_lexer **lexer, t_node *new, t_node *prev)
// {
//     if (!(*lexer) || !lexer)
//         return (FAILURE);
//     new->prev = prev;
//     new->next = prev->next;
//     (*lexer)->l_size ++;
//     if (!prev || !prev->next)
//         return (FAILURE);
//     return (SUCCESS);     
// }

