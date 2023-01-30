/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:25 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/30 17:40:50 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	if (!cmd[1])
		return (sort_and_print_env(*env, STDOUT_FILENO), EXIT_SUCCESS);
	i = 0;
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
			shleet_error(cmd[i], "not a valid identifier", 1);
	}
	return (EXIT_SUCCESS);
}
