/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_signel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:14:16 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/02 19:09:14 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrput_handler(int sig)
{
	(void)sig;	
	// if (g_global.is_runing)
	// 	return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);

	rl_redisplay();
	g_global.status = EXIT_FAILURE;
}


// int	termset(int stat)
// {
// 	struct termios	term;
// 	tcgetattr(STDOUT_FILENO, &term);
// 	if (stat)
// 		term.c_lflag &= ~(ECHOCTL);
	
// 	else
// 		term.c_lflag |= ECHOCTL;
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
// 		return (123);
// }

void init_terminal(void)
{
	// struct termios terminal;
	if (signal(SIGINT, interrput_handler) == SIG_ERR ||
	
	signal(SIGQUIT, SIG_IGN) == SIG_ERR || 
	
	signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		shleet_error("signal", strerror(errno), 2);
	
	// if (signal(SIGINT, SIG_DFL) == SIG_ERR || \
	// 	signal(SIGQUIT, SIG_DFL) == SIG_ERR || \
	// 	signal(SIGTSTP, SIG_DFL) == SIG_ERR)
	
}
