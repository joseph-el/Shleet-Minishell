# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 00:34:14 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/17 00:45:59 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     	:= minishell
LEXER 	 	:= lexer
EXPENDER 	:= exp
PARSE    	:= parse
EXEC     	:= exec

SRC_LEXER	:= ./srcs/lexer/lexer_utils.c ./srcs/lexer/lexer.c ./srcs/lexer/syntax.c
LIB 		:= ./libtools/libtools.a ./libgc/gc.a
UTILS 		:= ./srcs/utils/management_list.c

debug 		:= -fsanitize=address -g

all : 
	echo "minishell"
	
lexer : $(UTILS) $(SRC_LEXER) $(LIB)
		gcc $^ -o $(LEXER)

dlexer : $(UTILS) $(SRC_LEXER)
		gcc $(debug) $^ -o $(LEXER)

lib		: 
			@$(MAKE) -C libtools
			@$(MAKE) -C libgc

clean :
		rm $(NAME) $(LEXER) $ $(PARSE) $(EXEC)
	