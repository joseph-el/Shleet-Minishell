/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:28 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/03 19:55:29 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shleet_env(char **args)
{
	if (args && args[0])
		return (shleet_error("env", "too many arguments", STDERR_FILENO));
	else
		print_environment(g_global.envp, STDOUT_FILENO);
}
