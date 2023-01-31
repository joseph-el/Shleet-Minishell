/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:30 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/31 14:31:09 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_number(char *arg)
{
    int i;

    i = -1;
    while (arg[++i])
    {
        if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
        {
            i++;
            continue;
        }
        if (!ft_isdigit(arg[i]))
            return (false);
    }
    return (true);
}

void    exit_code(int status, bool mode)
{
    gc_purifying(&g_global.gc, CLEAN_ALL);
    //rl_clear_history();
    if (mode)
        exit(status);
    else
        exit(EXIT_SUCCESS);
}

void    shleet_exit(char **args)
{
    if (!args[0])
        exit_code(0, false);
    else if (!is_number(args[1]))
        return (shleet_error("exit", "numeric argument required", 2), exit_code(255, true));
    else if (args[1])
        return (shleet_error("exit", "too many arguments", 2));
    else
        exit_code(ft_atoi(args[0]), true);
}