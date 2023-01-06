# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 21:32:59 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/06 21:34:23 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := tree

debug := -fsanitize=address -gcc

all :
	gcc main.c -o $(NAME)

debug :
	gcc $(debug) main.c -o $(NAME)