/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:53:14 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/18 00:51:19 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


struct s_list *expand_tilde(t_lexer *exp)
{
    
}



t_list	*expander(t_list *tokens)
{
	t_node	*top;
	t_node	*next;

	while (top && top->tok != ENDOFCMD)
	{
		next = top->next;
		if (top->tok & REDIRECT)
            return (NULL);
		else if (top->tok & WILD)
			next = expand_tilde(top);
		else if (top->tok & REDIRECT)
			return (NULL); //handel
		else
			next = top->next;
		top = next;
	}

}