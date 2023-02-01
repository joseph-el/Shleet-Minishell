/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:35:08 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/01 20:35:48 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **export_to_array(t_env *head)
{
	char **ret;
	int		i;

	if (!head)
		return (NULL);
	i = size_environment(head);
	ret = gc(g_global.gc, malloc(sizeof(char *) * (i + 1)), TMP);
	if (!ret)
		return (NULL);
	i = 0;
	while (head)
	{
		ret[i++] = gc(g_global.gc, ft_strdup(head->type), TMP);
		head = head->next;
	}
	ret[i] = NULL;
	return (ret);
}

char	**sort_arr(char **env_type)
{
	int i;
	char	*tmp;

	i = 0;
	while (env_type[i])
	{
		if (env_type[i + 1] && ft_strcmp(env_type[i], env_type[i + 1]) > 0)
		{
			tmp = env_type[i];
			env_type[i] = env_type[i + 1];
			env_type[i + 1] = tmp;
			i = 0;
		}
		else
			i ++;
	}
	return (env_type);
}

void	print_exp_environment(t_env *env, char **sorted_arr, int fd)
{
	int		i;
	t_env	*hold;
	t_env	*tmp;

	if (!env)
		return ;
	tmp = env;
	i = 0;
	while (tmp)
	{
		ft_putstr_fd(place_holder , fd);
		hold = find_environment(env, sorted_arr[i]);
		ft_putstr_fd(hold->type, fd);
		print_exp_env(hold, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
		i++;
	}
}

char    **export_array(t_env *env)
{
    char    **ret;
    int     i;
    
    i = 0;
    ret = gc(g_global.gc, malloc(sizeof(char *) * size_environment(env) + 1), TMP);
    if (!ret)
        return (NULL);
    while (env)
    {
        ret[i++] = gc(g_global.gc, ft_strjoin(gc(g_global.gc, \
			ft_strjoin(env->type, "="), TMP), env->content), TMP);
		env = env->next;
    }
	ret[i] = NULL;
    return (ret);
}

void	join_and_insert(t_env **env, char *cmd)
{
	t_env	*hold;

	hold = find_environment(*env, type_environment(cmd));
	if (!hold)
		insert_environment(env, type_environment(cmd), \
			content_environment(cmd), cmd);
	else
		hold->content = gc(g_global.gc, \
			ft_strjoin(hold->content, content_environment(cmd)), OVR);
}
