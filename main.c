/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:45:04 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/07 09:53:12 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <paths.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>

typedef struct s_list
{
    char *data;
    struct s_list *next;
}               t_list;


typedef struct s_test
{
    t_list  *list;
    int     status;
    
}       t_test;

t_test  g_test;

void prin(t_list    *list)
{
    while (list)
    {
        fprintf(stderr, "===> |%s|\n", list->data);
        list = list->next;
    }
}

int main(int ac, char **av, char **env)
{
    t_list  *l1;
    t_list  *l2;
    t_list  *l3;

    l1 = malloc(sizeof(t_list));
    l2 = malloc(sizeof(t_list));
    l3 = malloc(sizeof(t_list));

    l1->data = strdup("HELLO");
    l2->data = strdup("JOSEPH");
    l3->data = strdup("LINA");

    l1->next = l2;
    l2->next = l3;
    l3->next = 0x0;

    g_test.list = l1;
    g_test.status = 0;

    pid_t   pid;

    pid = fork();

    if (pid == 0)
    {
        g_test.status = 11;
        g_test.list->data = strdup("EDITED");
        prin(g_test.list);
        exit(22);
    }
    wait(NULL);
    prin(g_test.list);
    puts("EXIT_SUCCESS");
    
    return 0;
}