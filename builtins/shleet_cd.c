/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:21 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/26 20:26:43 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "environment.h"

int	shleet_cd(char **cmd, t_env *env)
{
	char	*home;

	if (!cmd || !*cmd || !env)
		return (-1);
	if (!cmd[1])
	{
		home = get_environment(env, "HOME");
		if (!home)
			return (-1);
		return (chdir(home), 0);
	}
	chdir(cmd[1]);
	return (0);
}
