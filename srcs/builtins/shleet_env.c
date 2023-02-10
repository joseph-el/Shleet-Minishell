/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:28 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/10 21:49:29 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
