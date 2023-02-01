/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:25 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/01 20:02:23 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sort_and_print_env(t_env *env, int fd)
{
	char	**sorted_arr;

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

int key_isvalid(char *_env)
{
	int i;

	i = 0;
	if (!_env)
		return (false);
	if (_env[i] != '_' && !ft_isalpha(_env[i]))
		return (false);
	while (_env[i])
	{
		if ((_env[i] == '+' && _env[i + 1] == '=') || _env[i] == '=')
			break;
		if (!ft_isalnum(_env[i]) && _env[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	shleet_export(char **cmd, t_env **env)
{
	int 	i;

	if (!env)
		return (EXIT_FAILURE);
	if (!cmd[0])
		return (sort_and_print_env(*env, STDOUT_FILENO), EXIT_SUCCESS);
	i = -1;
	while (cmd[++i])
	{
		if (key_isvalid(cmd[i]))
		{
			if (is_joinable(cmd[i]))
				join_and_insert(env, cmd[i]);
			else
				insert_environment(env, type_environment(cmd[i]), \
					content_environment(cmd[i]), cmd[i]);
		}
		else
			shleet_error(cmd[i], "not a valid identifier", EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
