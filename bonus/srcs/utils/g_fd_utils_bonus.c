/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_fd_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:06:21 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:34:24 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	*io_save(void)
{
	int	*fds;

	fds = gc(g_global.gc, malloc(sizeof(int) * 2), OVR);
	if (!fds)
		return (NULL);
	fds[0] = dup(0);
	fds[1] = dup(1);
	if (fds[0] < 0 || fds[1] < 0)
		return (shleet_error("input output", "Failed to save", 1), NULL);
	return (fds);
}

void	reset_io(int *fds)
{
	int	ret1;
	int	ret2;

	ret1 = ft_dup2(fds[0], 0);
	ret2 = ft_dup2(fds[1], 1);
	if (ret1 < 0 || ret2 < 0)
		return (shleet_error("input output", "Failed to reset", 1));
}
