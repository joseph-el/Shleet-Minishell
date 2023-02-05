/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:21 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/05 16:58:59 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwds_data(void)
{
	t_env	*pwd_node;
	t_env	*oldpwd_node;
	char	cwd[PATH_MAX];

	if (!g_global.envp)
		return ;
	pwd_node = find_environment(g_global.envp, "PWD");
	oldpwd_node = find_environment(g_global.envp, "OLDPWD");
	if (!pwd_node || !oldpwd_node)
		return ;
	oldpwd_node->content = pwd_node->content;
	if (getcwd(cwd, sizeof(cwd)))
		pwd_node->content = gc(g_global.gc, ft_strdup(cwd), OVR);
}

int	shleet_cd(char **cmd_args)
{
	char	*home;

	if (!cmd_args[0])
	{
		home = get_environment(g_global.envp, "HOME");
		if (!home)
			return (shleet_error("cd", "HOME not found", 2), EXIT_FAILURE);
		if (chdir(home) == 0)
			return (update_pwds_data(), EXIT_SUCCESS);
		else
			return (shleet_error("cd", "HOME not set", 2), EXIT_FAILURE);
	}
	if (cmd_args[1])
		return (shleet_error("cd", "too many args", 2), EXIT_FAILURE);
	if (chdir(cmd_args[0]) == -1)
		return (shleet_error("cd", strerror(errno), 2), EXIT_FAILURE);
	return (update_pwds_data(), EXIT_SUCCESS);
}
