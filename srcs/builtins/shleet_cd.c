/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:21 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/02 00:17:20 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwds_data(t_env *env)
{
	t_env	*pwd_node;
	t_env	*oldpwd_node;
	char	cwd[PATH_MAX];

	if (!env)
		return ;
	pwd_node = find_environment(env, "PWD");
	oldpwd_node = find_environment(env, "OLDPWD");
	if (!pwd_node || !oldpwd_node)
		return ;
	pwd_node->content = oldpwd_node->content;
	if (getcwd(cwd, sizeof(cwd)))
		pwd_node->content = gc(g_global.gc, ft_strdup(cwd), OVR);
}

void	shleet_cd(char **cmd, t_env *env)
{
	char	*home;
	
	if (!cmd[0])
	{
		home = get_environment(env, "HOME");
		if (!home)
			return (shleet_error("cd", "HOME not set", 2));
		if (chdir(home) == 0)
			return (update_pwds_data(env));
		else
			return;
	}
	fprintf(stderr, "check path |%s|\n", cmd[0]);
	if (chdir(cmd[0]) == -1)
		return (shleet_error(cmd[0], strerror(errno), 1));
	return (update_pwds_data(env));
}
