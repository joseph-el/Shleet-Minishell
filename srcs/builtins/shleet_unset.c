/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/31 14:19:41 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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