/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_env_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:28 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/12 12:32:46 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	shleet_env(char **args)
{
	if (args && args[0])
		return (shleet_error("env", "too many arguments", STDERR_FILENO));
	else
	{
		g_global.status = 0;
		print_environment(g_global.envp, STDOUT_FILENO);
	}
}
