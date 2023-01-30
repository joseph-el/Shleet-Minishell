/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:25 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/30 14:20:55 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	print_exp_environment(env, sorted_arr, fd);
	return (EXIT_SUCCESS);
}

int	is_joinable(char *_env)
{
	int	i;

	if (!_env)
		return (false);
	i = 0;
	while (_env[i] && _env[i] != '=')
        i++;
	return ((_env[i] == '=' && _env[i - 1] == '+'));
}

int	shleet_export(char **cmd, t_env **env)
{
	t_env	*hold;
	int 	i;

	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	if (!cmd[1])
		return (sort_and_print_env(*env, STDOUT_FILENO), EXIT_SUCCESS);
	i = 0;
	while (cmd[++i])
	{
		if (is_joinable(cmd[i]))
		{
			hold = find_environment(*env, type_environment(cmd[i]));
			if (!hold)
				insert_environment(env, type_environment(cmd[i]), \
					content_environment(cmd[i]), cmd[i]);
			else
				hold->content = gc(g_global.gc, \
					ft_strjoin(hold->content, content_environment(cmd[i])), OVR);
		}
		else
			insert_environment(env, type_environment(cmd[i]), \
				content_environment(cmd[i]), cmd[i]);
	}
	return (EXIT_SUCCESS);
}
