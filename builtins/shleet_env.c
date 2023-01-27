/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:28 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/27 11:04:50 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "environment.h"
# include <stdbool.h>
# include <stdio.h>

void    shleet_env(t_env *env)
{
    if (!env)
        ft_putstr_fd("(null)", 1);
    print_environment(env);
}
