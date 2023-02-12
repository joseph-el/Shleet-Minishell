/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:07:13 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:34:34 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_global	g_global = {.gc = NULL, .envp = NULL, .status = 0, .fd_io = NULL};

void	set_global(char **envp, t_expander **l_expander, t_lexer **l_lexer)
{
	g_global.gc = gc_init();
	if (!g_global.gc)
		return (shleet_error("malloc", strerror(ENOMEM), 1), exit(1));
	g_global.envp = init_environment(envp);
	g_global.fd_io = io_save();
	*l_expander = NULL;
	*l_lexer = NULL;
}

int	main(int argc, char **args, char **envp)
{
	t_expander	*l_expander;
	t_lexer		*l_lexer;
	char		*line;

	(void)argc;
	(void)args;
	set_global(envp, &l_expander, &l_lexer);
	while (true)
	{
		init_signal();
		line = readline(GREEN "Shleet-Minishell>$ " WHITE);
		if (!line)
			break ;
		gc_adding_adress(g_global.gc, line, TMP);
		l_lexer = lexer(line);
		l_expander = expander(l_lexer);
		executor(l_expander);
		gc_purifying(&g_global.gc, CLEAN_TMP);
	}
	clean_out();
	return (EXIT_SUCCESS);
}
