# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 21:47:57 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/16 15:00:48 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lexer


SRC := lexer.c lexer_utils.c ../../libgc/gc.a syntax.c

debug := -fsanitize=address -g

all : $(SRC)
	gcc $^ -o $(NAME)

debug : $(SRC)
	gcc $(debug) $^ -o $(NAME)
