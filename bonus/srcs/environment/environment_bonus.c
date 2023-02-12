/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:24:27 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:47:45 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_env	*new_environment(char *content, char *type)
{
	t_env	*node_environment;

	node_environment = gc(g_global.gc, malloc(sizeof(t_env)), OVR);
	if (!node_environment)
		return (NULL);
	node_environment->next = NULL;
	node_environment->prev = NULL;
	node_environment->content = content;
	node_environment->type = type;
	node_environment->is_var = 0;
	return (node_environment);
}

t_env	*insert_environment(t_env **envs, char *type, char *content, char *env)
{
	t_env	*tmp_environment;
	t_env	*new_env;

	if (*envs == NULL)
	{
		new_env = new_environment(content, type);
		if (env && ft_strchr(env, '='))
			new_env->is_var = 1;
		return (*envs = new_env, NULL);
	}
	tmp_environment = (*envs);
	while (tmp_environment->next)
		tmp_environment = tmp_environment->next;
	new_env = new_environment(content, type);
	if (ft_strchr(env, '='))
		new_env->is_var = 1;
	tmp_environment->next = new_env;
	new_env->prev = tmp_environment;
	return (*envs);
}

t_env	*init_environment(char **env)
{
	t_env	*envs;
	int		index;

	if (!env)
		return (NULL);
	envs = NULL;
	index = -1;
	while (env && env[++index])
		insert_environment(&envs, type_environment(env[index]), \
		content_environment(env[index]), env[index]);
	if (!find_environment(envs, "PATH"))
		insert_environment(&envs, gc(g_global.gc, ft_strdup("PATH"), OVR), \
			gc(g_global.gc, ft_strdup(_PATH_STDPATH), OVR), NULL);
	return (envs);
}
