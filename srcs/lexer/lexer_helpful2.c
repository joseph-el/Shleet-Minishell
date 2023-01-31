/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpful.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:59:26 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/31 20:01:01 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*handle_state(t_list  *l_lexer, char *l_cmd)
{
	t_token	tok1;
	t_token tok2;
	t_token	type;
	int		cr[2];

	cr[0] = *l_cmd;
	cr[1] = *(l_cmd + 1);
	tok1 = (cr[0] == '|') * PIPE + (cr[0] == '>') * GREAT + \
		(cr[0] == '<') * LESS + (cr[0] == '&') * AND;
	tok2 = (cr[1] == '|') * PIPE + (cr[1] == '>') * GREAT + \
		 (cr[1] == '<') * LESS + (cr[1] == '&') * AND;
	type = (tok1 == PIPE && tok2 == PIPE) * OR + (tok1 == GREAT && tok2 == GREAT) * \
		APPEND + (tok1 == LESS && tok2 == LESS) * HERDOC + (tok1 == AND && tok2 == AND) * AND;
	if (tok1 && tok2)
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 2), type));
	else if (tok1 != AND)
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 1), tok1));
	else
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, 1), WORD));
	return (l_cmd + ((tok1 && tok2) + (tok1 != 0)));
}

char	*normal_stat(t_list *l_lexer, char *l_cmd)
{
	bool	mode;
	int		len;

	len = 0;
	while (l_cmd[len] && !ft_strchr("\'\"$<>&|()", l_cmd[len]) && !ft_isspace(l_cmd[len]))
	{
		if (l_cmd[len] == '*')
			mode = true;
		len++;
	}
	if (!mode)
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WORD));
	else
		push_back(&l_lexer, creat_node(ft_strndup(l_cmd, len), WILD));
	return (l_cmd + len);
}

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

t_list	*set_token(char *l_cmd)
{
	t_list	*l_lexer;

	l_lexer = new_list();
	if (!l_lexer)
		return (NULL);
	push_back(&l_lexer, creat_node(NULL, BEGINOFCMD));
	while (*l_cmd && *l_cmd != NEWLINE)
	{
		if (ft_isspace(*l_cmd))
			l_cmd = whitespace(l_lexer, l_cmd);
		else if (*l_cmd == '\'')
			l_cmd = s_quote(l_lexer, l_cmd + 1);
		else if (*l_cmd == '\"')
			l_cmd = d_quote(l_lexer, l_cmd + 1);
		else if (*l_cmd == DOLLAR)
			l_cmd = dollar(l_lexer, l_cmd);
		else if (*l_cmd == '(' || *l_cmd == ')')
			l_cmd = parentheses(l_lexer, l_cmd);
		else if (ft_strchr("<&|>", *l_cmd))
			l_cmd = handle_state(l_lexer, l_cmd);
		else
			l_cmd = normal_stat(l_lexer, l_cmd);
	}
	push_back(&l_lexer, creat_node(NULL, ENDOFCMD));
	return (l_lexer);
}