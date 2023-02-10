/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpful1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:19:01 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/10 17:07:34 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*s_quote(t_list *l_lexer, char *l_cmd)
{
	int	len;

	push_back(&l_lexer, creat_node(ft_strdup("\'"), SQUOTE));
	len = 0;
	while (l_cmd[len] && l_cmd[len] != NEW_LINE && l_cmd[len] != '\'')
		len++;
	if (len)
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WORD));
	if (l_cmd[len] == '\'')
		push_back(&l_lexer, creat_node(ft_strdup("\'"), SQUOTE));
	return (l_cmd + (len + (l_cmd[len] == '\'')));
}

char	*dollar(t_list *l_lexer, char *l_cmd)
{
	int	len;

	if (*(l_cmd + 1) && *(l_cmd + 1) == '?')
	{
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 2), VAR));
		return (l_cmd + 2);
	}
	len = 0;
	while (l_cmd[len + 1] && (l_cmd[len + 1] == '_' || \
		ft_isalnum(l_cmd[len + 1])))
		len++;
	if (len)
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), VAR));
	else
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 1), WORD));
	return (l_cmd + len + 1);
}

int	bare_quotes(t_lexer *l_lexer, char *l_cmd)
{
	push_back(&l_lexer, creat_node(ft_strdup("\""), DQUOTE));
	if (*l_cmd && *l_cmd == '\"')
	{
		push_back(&l_lexer, creat_node(ft_strdup(""), WORD));
		push_back(&l_lexer, creat_node(ft_strdup("\""), DQUOTE));
		return (true);
	}
	return (false);
}

char	*d_quote(t_list *l_lexer, char *l_cmd)
{
	int	len;

	len = 0;
	if (bare_quotes(l_lexer, l_cmd))
		return (l_cmd + 1);
	while (l_cmd[len] && l_cmd[len] != NEW_LINE && l_cmd[len] != '\"')
	{
		if (l_cmd[len] == DOLLAR)
		{
			if (len)
				push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WORD));
			l_cmd = dollar(l_lexer, l_cmd + len);
			len = 0;
		}
		else
			len++;
	}
	if (len)
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WORD));
	if (l_cmd[len] == '\"')
		push_back(&l_lexer, creat_node(ft_strdup("\""), DQUOTE));
	return (l_cmd + (len + (l_cmd[len] == '\"')));
}

char	*parentheses(t_list *l_lexer, char *l_cmd)
{
	int	target;

	target = (l_cmd[0] == ')') * RPAR + (l_cmd[0] == '(') * LPAR;
	push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 1), target));
	return (l_cmd + 1);
}
