# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 00:34:14 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/17 18:40:11 by yoel-idr         ###   ########.fr        #
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
	
lexer : clean
		@echo "\nNo error\n"
		@gcc $(UTILS) $(SRC_LEXER) $(LIB) ./srcs/minishell.c -o $(LEXER)

dlexer : $(UTILS) $(SRC_LEXER)
		gcc $(debug) $^ -o $(LEXER)

lib		: 
			@$(MAKE) -C libtools
			@$(MAKE) -C libgc

clean :
		@rm -drf $(NAME) $(LEXER) $ $(PARSE) $(EXEC)

fclean : clean
			@echo "\nClean ~\n"
			@$(MAKE) -C libtools fclean
			@$(MAKE) -C libgc fclean
		