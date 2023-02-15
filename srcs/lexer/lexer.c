/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:53:06 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/13 18:49:08 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer(char *cmdline)
{
	t_lexer	*l_lexer;

	if (!ft_isspace(*cmdline))
		add_history(cmdline);
	l_lexer = set_token(cmdline);
	if (!l_lexer)
		return (NULL);
	if (!syntax(l_lexer))
	{
		g_global.status = (258 * 256);
		return (NULL);
	}
	return (l_lexer);
}
