/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:23 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/02 00:10:50 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shleet_pwd(char **cmd)
{
	char	cwd[PATH_MAX];

	if (cmd[0])
		return (ft_putstr_fd("Args Not Required by the subject\n", \
			STDERR_FILENO), EXIT_FAILURE);

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		return (ft_putstr_fd("\n", STDOUT_FILENO), EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
