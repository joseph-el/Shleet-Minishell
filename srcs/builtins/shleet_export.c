/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:25 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/28 22:48:19 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# define place_holder "declare -x "

char **export_to_array(t_env *head)
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

int	sort_and_print_env(t_env *env, int fd)
{
	int		i;
	char	**sorted_arr;
	t_env	*tmp;
	t_env	*hold;

	if (!env)
		return (EXIT_FAILURE);
	sorted_arr = sort_arr(export_to_array(env));
	if (!sorted_arr)
		return (EXIT_FAILURE);
	i = 0;
	tmp = env;
	while (tmp)
	{
		// CHECK CHECK
		ft_putstr_fd(place_holder , fd);
		hold = find_environment(env, sorted_arr[i]);
		ft_putstr_fd(hold->type, fd);
		if (!hold->content)
			return (ft_putstr_fd("\n", fd), EXIT_SUCCESS);
		ft_putstr_fd("=", fd);
		ft_putchar_fd("\"", fd);
		ft_putstr_fd(get_environment(env, sorted_arr[i]), fd);
		ft_putchar_fd("\"", fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * @return 
*/
int	shleet_export(char **cmd, t_env *env, int fd)
{
	int i;

	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	if (!cmd[1])
		return (sort_and_print_env(env, fd), EXIT_SUCCESS);
	i = 0;
	// HERE
	return (EXIT_SUCCESS);
}
