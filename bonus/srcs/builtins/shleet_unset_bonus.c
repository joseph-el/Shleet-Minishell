/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_unset_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/12 12:32:56 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	unset_node(char *type)
{
	t_env	*target_env;
	t_env	*tmp;

	target_env = find_environment(g_global.envp, type);
	if (!target_env)
		return ;
	if (!target_env->prev && !target_env->next)
		g_global.envp = NULL;
	if (!target_env->prev)
	{
		g_global.envp = (g_global.envp)->next;
		(g_global.envp)->prev = NULL;
		return ;
	}
	if (!target_env->next)
	{
		target_env->prev->next = NULL;
		return ;
	}
	tmp = target_env->next;
	target_env->prev->next = tmp;
	target_env->prev = NULL;
	target_env->next = NULL;
}

void	shleet_unset(char **args)
{
	int		i;

	if (!g_global.envp || !args || !*args)
		return ;
	i = -1;
	while (args[++i])
		unset_node(type_environment(args[i]));
	g_global.status = 0;
}
