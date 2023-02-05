/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:09:46 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/01 13:34:19 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shleet_error(char *error_msg, char *specify, int status)
{
	ft_putstr_fd("Shleet-Minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	if (specify)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(specify, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	g_global.status = status;
}