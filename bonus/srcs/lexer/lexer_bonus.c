/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:53:06 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 12:34:03 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
