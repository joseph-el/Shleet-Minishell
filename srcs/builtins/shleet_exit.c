/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:30 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/29 16:51:37 by aelkhali         ###   ########.fr       */
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
        gc_purifying(g_global.gc, ALL);
        exit(EXIT_SUCCESS);
    }
    i = -1;
    while (cmd[++i])
    {
        if (!ft_isdigit(cmd[i]))
        {
            ft_putstr_fd("numeric argument required", STDERR_FILENO);
            gc_purifying(g_global.gc, ALL);
            exit(EX_STATUS);
        }
    }
    status = ft_atoi(status);
    gc_purifying(g_global.gc, ALL);
    exit(status);
    return (EXIT_SUCCESS);
}
