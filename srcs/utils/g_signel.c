/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_signel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:14:16 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 19:31:52 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	interrput_handler(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(EXIT_FAILURE);
}

void init_terminal(void)
{
	struct termios terminal;
	
}
