/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_signel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:14:16 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/10 22:15:13 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrput_handler(int sig)
{
	(void)sig;	
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_global.status = 256;
}

int	shleet_status(void)
{
	if (WIFEXITED(g_global.status))
		return (WEXITSTATUS(g_global.status));
	if (WIFSTOPPED(g_global.status))
		return (128 + WSTOPSIG(g_global.status));
	if (WIFSIGNALED(g_global.status))
		return (128 + WTERMSIG(g_global.status));
	return (EXIT_FAILURE);
}

void init_signal(void)
{
	if (signal(SIGINT, interrput_handler) == SIG_ERR ||
	signal(SIGQUIT, SIG_IGN) == SIG_ERR || 
	signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		shleet_error("signal", strerror(errno), 1);
}
