/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_export_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:25 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/12 18:05:58 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	sort_and_print_env(int fd)
{
	char	**sorted_arr;

	if (!g_global.envp)
		return (EXIT_FAILURE);
	sorted_arr = sort_arr(export_to_array(g_global.envp));
	if (!sorted_arr)
		return (EXIT_FAILURE);
	print_exp_environment(g_global.envp, sorted_arr, fd);
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

int	key_isvalid(char *_env)
{
	int	i;

	i = 0;
	if (!_env)
		return (false);
	if (_env[i] != '_' && !ft_isalpha(_env[i]))
		return (false);
	while (_env[i])
	{
		if ((_env[i] == '+' && _env[i + 1] == '=') || _env[i] == '=')
			break ;
		if (!ft_isalnum(_env[i]) && _env[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	delete_and_insert(char *cmd)
{
	t_env	*tmp;

	if (!cmd)
		return ;
	tmp = find_environment(g_global.envp, type_environment(cmd));
	if (tmp)
		delete_environment(&tmp);
	insert_environment(&g_global.envp, type_environment(cmd), \
		content_environment(cmd), cmd);
}

void	shleet_export(char **cmd)
{
	int		i;
	int		status;

	if (!g_global.envp)
		return ;
	status = 0;
	if (!cmd[0])
	{
		g_global.status = 0;
		return ((void)sort_and_print_env(STDOUT_FILENO));
	}
	i = -1;
	while (cmd[++i])
	{
		if (key_isvalid(cmd[i]))
		{
			if (is_joinable(cmd[i]))
				join_and_insert(&g_global.envp, cmd[i]);
			else
				delete_and_insert(cmd[i]);
		}
		else
		{
			status = 1;
			shleet_error(cmd[i], "not a valid identifier", EXIT_FAILURE);
		}
	}
	g_global.status = status;
}
