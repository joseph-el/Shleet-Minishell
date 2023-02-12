/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:48:38 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 01:15:38 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expander	*expander(t_lexer *l_lexer)
{
	t_expander	*l_expander;
	int			status;

	if (!l_lexer)
		return (NULL);
	l_expander = new_explist();
	if (!l_expander)
		return (NULL);
	status = set_expand(l_expander, l_lexer);
	if (status)
	{
		shleet_error("expander", "syntax error", 2);
		return (NULL);
	}
	return (l_expander);
}
