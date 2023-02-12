/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:51:40 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 01:15:38 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close(int fds[2], int fd_tmp)
{
	int	ret;

	close(fd_tmp);
	ret = dup(fds[0]);
	close(fds[WIRITE_]);
	close(fds[READ_]);
	return (ret);
}

bool	is_builtins(char *arg)
{
	unsigned long	len;

	len = sizeof(arg) + 1;
	if (
		!ft_strncmp(arg, "echo", len) || \
		!ft_strncmp(arg, "exit", len) || \
		!ft_strncmp(arg, "pwd", len) || \
		!ft_strncmp(arg, "unset", len) || \
		!ft_strncmp(arg, "cd", len) || \
		!ft_strncmp(arg, "env", len) || \
		!ft_strncmp(arg, "export", len))
		return (true);
	return (false);
}

bool	is_pipe(t_cmdexc *head_grp)
{
	if (!head_grp)
		return (false);
	while (head_grp)
	{
		if (head_grp->node_type == NODE_PIPE)
			return (true);
		head_grp = head_grp->next;
	}
	return (false);
}

void	clean_out(void)
{
	gc_purifying(&g_global.gc, CLEAN_ALL);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
