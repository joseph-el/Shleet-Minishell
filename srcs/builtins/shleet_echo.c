/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:36:30 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/29 19:24:59 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_arg(char *cmd_arg)
{
	int	i;

	i = 1;
	if (!cmd_arg)
		return (false);
	if (*cmd_arg == '-')
	{
		while (cmd_arg[i])
		{
			if (cmd_arg[i] == 'n' && !cmd_arg[i + 1])
				return (true);
			if (cmd_arg[i] != 'n')
				break ;
			i++;
		}
	}
	return (false);
}

int	shleet_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	if (!cmd[1])
		return (ft_putstr_fd("\n", STDOUT_FILENO), EXIT_SUCCESS);
	if (cmd[1] && check_arg(cmd[1]))
		i = 2;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
		if (!cmd[i])
			break ;
		ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!check_arg(cmd[1]))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
