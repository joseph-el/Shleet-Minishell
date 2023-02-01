/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/01 11:29:07 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_node(t_env **env, char *type)
{
	t_env	*target_env;
	t_env	*tmp;

	target_env = find_environment(*env, type);
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

void	shleet_unset(t_env **env, char **args)
{
	int i;

	if (!env || !args || !*args)
		return ;
	i = -1;
	while (args[++i])
		unset_node(env, args[i]);
}