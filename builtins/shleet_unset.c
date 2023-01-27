/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/27 14:13:02 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	shleet_unset(t_env **env, char *type)
{
	t_env	*tmp;
    
	if (!find_environment(*env, type))
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	tmp = (*env);
	while (tmp)
	{
		if (!ft_memcmp(tmp->type, type, sizeof(type) + 1))
			remove_environment(env, type);
		tmp = tmp->next;
	}
}
