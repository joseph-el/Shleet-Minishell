/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_pwd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:23 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/12 01:15:38 by yoel-idr         ###   ########.fr       */
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

void	shleet_pwd(char **cmd_args)
{
	t_env	*pwd;

	if (!cmd_args[0])
	{
		pwd = find_environment(g_global.envp, "PWD");
		if (!pwd)
		{
			g_global.status = 0;
			return ((void)get_cwd());
		}
		ft_putstr_fd(pwd->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_global.status = 0;
		return ;
	}
	shleet_error("pwd", "Args and options Not required by the subject !", 1);
}
