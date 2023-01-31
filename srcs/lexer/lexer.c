/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:55:19 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 20:01:52 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*lexer(char *cmdline)
{
	t_lexer *l_lexer;

	l_lexer = set_token(cmdline);
	if (!l_lexer)
		return (NULL);
	if (!syntax(l_lexer))
	{
		// g_global.status = 2;
		return (NULL);
	}
	return (l_lexer);
}
