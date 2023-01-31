/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:36:30 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/30 17:53:06 by aelkhali         ###   ########.fr       */
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

	i = 0;
	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	if (!cmd[i])
		return (ft_putstr_fd("\n", STDOUT_FILENO), EXIT_SUCCESS);
	if (cmd[i] && check_arg(cmd[i]))
		i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
		if (!cmd[i])
			break ;
		ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!check_arg(cmd[0]))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
