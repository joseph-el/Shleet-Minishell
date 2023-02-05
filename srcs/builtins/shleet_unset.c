/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/03 20:03:29 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_node(t_env **env, char *type)
{
	t_env	*target_env;
	t_env	*tmp;

	target_env = find_environment(*env, type);
	if (!target_env)
		return ;
	if (!target_env->prev && !target_env->next)
		(*env) = NULL;
	if (!target_env->prev)
	{
		(*env) = (*env)->next;
		(*env)->prev = NULL;
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
	t_env	*env;
	int		i;

	env = g_global.envp;
	if (!env || !args || !*args)
		return ;
	i = -1;
	while (args[++i])
		unset_node(&env, type_environment(args[i]));
}
