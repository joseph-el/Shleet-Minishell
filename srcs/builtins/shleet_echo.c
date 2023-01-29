/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:36:30 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/29 17:45:50 by yoel-idr         ###   ########.fr       */
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

int	shleet_echo(char **cmd, int fd)
{
	int	i;

	i = 1;
	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	if (!cmd[1])
		return (ft_putstr_fd("\n", fd), EXIT_SUCCESS);
	if (cmd[1] && check_arg(cmd[1]))
		i = 2;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], fd);
		if (!cmd[i])
			break ;
		ft_putstr_fd(" ", fd);
	}
	if (!check_arg(cmd[1]))
		ft_putstr_fd("\n", fd);
	return (EXIT_SUCCESS);
}
