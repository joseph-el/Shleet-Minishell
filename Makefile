# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 13:30:43 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/06 21:25:20 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRC := ./srcs/minishell

debug := -fsanitize=address -g

all : $(SRC)
	gcc $^ -o $(NAME)

debug : $(SRC)
		gcc $(debug) -o $(NAME)

