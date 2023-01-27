/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:36:30 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/27 14:04:04 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

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
	if (!cmd || !*cmd || ft_strncmp(cmd[0], "echo", 5))
		return (EXIT_FAILURE);
	if (!cmd[1])
		return (ft_putchar_fd('\n', fd), EXIT_SUCCESS);
	if (cmd[1] && check_arg(cmd[1]))
		i = 2;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], fd);
		if (!cmd[i])
			break ;
		ft_putchar_fd(' ', fd);
	}
	if (!check_arg(cmd[1]))
		ft_putchar_fd('\n', fd);
	return (EXIT_SUCCESS);
}
