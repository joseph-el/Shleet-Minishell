/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:09:46 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/14 18:30:32 by yoel-idr         ###   ########.fr       */
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
	g_global.status = (status * 256);
}

pid_t	ft_fork(void)
{
	pid_t	_pid;

	_pid = fork();
	if (_pid)
	{
		shleet_error("fork", "unable to creat a process", 1);
		return (-1);
	}
	return (_pid);
}

int	ft_dup2(int fd1, int fd2)
{
	int	ret;

	ret = dup2(fd1, fd2);
	if (ret)
	{
		shleet_error("dup2", "unable to duplicate", 1);
		return (-1);
	}
	return (2);
}

int	ft_pipe(int fds[2])
{
	int	ret;

	ret = pipe(fds);
	if (ret)
	{
		shleet_error("pipe", "unable to create a pipe", 1);
		return (-1);
	}
	return (ret);
}
