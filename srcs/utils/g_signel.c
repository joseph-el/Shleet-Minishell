/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_signel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:14:16 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/05 11:04:43 by aelkhali         ###   ########.fr       */
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
	g_global.status = 1;
}


void init_terminal(void)
{
	// struct termios terminal;
	if (signal(SIGINT, interrput_handler) == SIG_ERR ||
	
	signal(SIGQUIT, SIG_IGN) == SIG_ERR || 
	
	signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		shleet_error("signal", strerror(errno), 1);
	
	// if (signal(SIGINT, SIG_DFL) == SIG_ERR || \
	// 	signal(SIGQUIT, SIG_DFL) == SIG_ERR || \
	// 	signal(SIGTSTP, SIG_DFL) == SIG_ERR)
	
}
