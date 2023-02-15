/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/14 18:30:04 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_node(char *type)
{
	t_env	*target_env;
	char 	*env_utils;

	target_env = find_environment(g_global.envp, type);
	if (!target_env)
		return ;
	if (!target_env->prev)
	{
		g_global.envp = (g_global.envp)->next;
		if (g_global.envp)
			(g_global.envp)->prev = NULL;
		return ;
	}
	if (!target_env->next)
	{
		if (target_env->prev)
			target_env->prev->next = NULL;
		return ;
	}
	target_env->prev->next = target_env->next;
	target_env->next->prev = target_env->prev;
}

void	shleet_unset(char **args)
{
	int		i;
	int		status;

	if (!g_global.envp || !args || !*args)
		return ;
	status = 0;
	i = -1;
	while (args[++i])
	{
		if (key_isvalid(args[i]))
			unset_node(type_environment(args[i]));
		else
		{
			shleet_error(args[i], "not a valid identifier", EXIT_FAILURE);
			status = 1;
		}
	}
	g_global.status = status;
}
