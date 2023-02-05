/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:23 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/03 20:03:11 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) < 0)
		return (EXIT_FAILURE);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	shleet_pwd(char **cmd_args)
{
	t_env	*pwd;

	if (!cmd_args[0])
	{
		pwd = find_environment(g_global.envp, "PWD");
		if (!pwd)
			return (get_cwd(), EXIT_SUCCESS);
		ft_putstr_fd(pwd->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	shleet_error("pwd", "Args and options Not required by the subject !", 1);
	return (EXIT_FAILURE);
}
