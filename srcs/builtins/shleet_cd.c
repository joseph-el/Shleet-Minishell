/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:21 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/29 15:45:40 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	shleet_cd(char **cmd, t_env *env)
{
	char	*home;

	if (!cmd || !*cmd || !env)
		return (EXIT_FAILURE);
	if (!cmd[1])
	{
		home = get_environment(env, "HOME");
		if (!home)
			return (EXIT_FAILURE);
		if (chdir(home) == 0)
			return (update_pwds_data(env), EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	if (chdir(cmd[1]) == -1)
		return (EXIT_FAILURE);
	return (update_pwds_data(env), EXIT_SUCCESS);
}
