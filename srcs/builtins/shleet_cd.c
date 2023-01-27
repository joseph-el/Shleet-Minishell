/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:21 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/27 20:49:40 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	shleet_cd(char **cmd, t_env *env)
{
	// CHANGE PWD IN ENV PATHS
	char	*home;

	if (!cmd || !*cmd || !env)
		return (EXIT_FAILURE);
	if (!cmd[1])
	{
		home = get_environment(env, "HOME");
		if (!home)
			return (EXIT_FAILURE);
		if (!chdir(home))
		{
			//update l PWD
			//update l OLDPWD
			return (EXIT_SUCCESS);
		}
		else
			return (EXIT_FAILURE);
	}
	if (chdir(cmd[1]) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
