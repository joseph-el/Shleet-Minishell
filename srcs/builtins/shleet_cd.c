/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:21 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/11 14:06:41 by aelkhali         ###   ########.fr       */
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
	oldpwd_node->content = gc(g_global.gc, ft_strdup(pwd_node->content), OVR);
	if (getcwd(cwd, sizeof(cwd)))
		pwd_node->content = gc(g_global.gc, ft_strdup(cwd), OVR);
}

void	shleet_cd(char **cmd_args)
{
	t_env	*home;

	if (!cmd_args[0])
	{
		home = find_environment(g_global.envp, "HOME");
		if (!home)
			return (shleet_error("cd", "HOME not found", 2));
		if (chdir(home->content) == 0)
		{
			g_global.status = 0;
			return (update_pwds_data());
		}
		else
			return (shleet_error("cd", "HOME not set", 2));
	}
	if (cmd_args[1])
		return (shleet_error("cd", "too many args", 2));
	if (!*cmd_args[0])
		return ;
	if (chdir(cmd_args[0]) == -1)
		return (shleet_error("cd", strerror(errno), 2));
	g_global.status = 0;
	return (update_pwds_data());
}
