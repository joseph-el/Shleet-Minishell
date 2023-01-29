/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:19:01 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/29 17:14:07 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*whitespace(t_list *l_lexer, char *l_cmd)
{
	int	len;

	len = 0;
	while (l_cmd[len] && l_cmd[len] != NEWLINE && ft_isspace(l_cmd[len]))
		len++;
	if (len)
		push_back(&l_lexer, creat_node(NULL, WSPACE));
	return (l_cmd + len);
}

char	*s_quote(t_list *l_lexer, char *l_cmd)
{
	int	len;

	push_back(&l_lexer, creat_node(ft_strdup("\'"), SQUOTE));
	len = 0;
	while (l_cmd[len] && l_cmd[len] != NEWLINE && l_cmd[len] != '\'')
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
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 2), RECENTEXC));
		return (l_cmd + 2);
	}
	len = 0;
	len += (*l_cmd == DOLLAR);
	while (l_cmd[len] && (l_cmd[len] == '_' || ft_isalnum(l_cmd[len])))
		len++;
	if (len)
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), VAR));
	else
	{
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 1), WORD));
		len++;
	}
	return (l_cmd + len);
}

char	*d_quote(t_list *l_lexer, char *l_cmd)
{
	int		len;

	len = 0;
	push_back(&l_lexer, creat_node(ft_strdup("\""), DQUOTE));
	while (l_cmd[len] && l_cmd[len] != NEWLINE && l_cmd[len] != '\"')
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
	int target;

	target = (l_cmd[0] == ')') * RPAR + (l_cmd[0] == '(') * LPAR;
	push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 1), target));
	return (l_cmd + 1);
}