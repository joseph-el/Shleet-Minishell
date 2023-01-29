/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:30 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/29 18:24:13 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# define EX_STATUS 255

int     shleet_exit(char *cmd)
{
    int i;
    int status;

    if (!cmd)
    {
        gc_purifying(g_global.gc, CLEAN_ALL);
        exit(EXIT_SUCCESS);
    }
    i = -1;
    while (cmd[++i])
    {
        if (!ft_isdigit(cmd[i]))
        {
            ft_putstr_fd("numeric argument required", STDERR_FILENO);
            gc_purifying(g_global.gc, CLEAN_ALL);
            exit(EX_STATUS);
        }
    }
    status = ft_atoi(status);
    gc_purifying(g_global.gc, CLEAN_ALL);
    exit(status);
    return (EXIT_SUCCESS);
}
