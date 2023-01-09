/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:55:42 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/09 18:57:42 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct s_list
{
    char    *data;
    int     size;
    struct s_list   *next;
    struct s_list   *prev;
}               t_list;
