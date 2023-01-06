/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:23:49 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/06 21:22:43 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main(int ac, char **av)
{
    t_parce data;

    data.cmd = av[1];
    

    readline("minishell");



    
    return (EXIT_SUCCESS);
}