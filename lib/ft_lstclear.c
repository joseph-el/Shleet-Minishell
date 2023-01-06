/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:27:03 by yoel-idr          #+#    #+#             */
/*   Updated: 2022/10/19 08:29:49 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*k;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		k = (*lst);
		(*lst) = (*lst)->next;
		ft_lstdelone(k, del);
	}
}
