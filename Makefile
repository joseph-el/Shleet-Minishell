# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 14:33:17 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/27 19:14:05 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     	:= minishell
LEXER 	 	:= lexer
EXPENDER 	:= exp
PARSE    	:= parse
EXEC     	:= exec

SRC_LEXER	:= ./srcs/lexer/lexer_utils.c ./srcs/lexer/lexer.c ./srcs/lexer/syntax.c
LIB 		:= ./libtools/libtools.a ./gc_memory/gc_memory.a
UTILS 		:=  ./srcs/utils/list_destroyer.c ./srcs/utils/list_construct.c ./srcs/utils/g_error.c
EXP			:= ./srcs/expander/wildcard.c ./srcs/expander/io_utils.c ./srcs/expander/expander.c  ./srcs/expander/list_utils.c ./srcs/expander/utils.c
debug 		:= -fsanitize=address -g3

all : 
	echo "minishell"
	
lexer : clean
		@echo "\nNo error\n"
		@gcc -lreadline $(UTILS) $(SRC_LEXER) $(LIB) $(EXP) ./srcs/minishell.c -o $(LEXER)

dlexer : $(UTILS) $(SRC_LEXER)
		@echo "\nLexer debug\n"
		@gcc $(debug) -lreadline $(UTILS) $(SRC_LEXER) $(LIB) $(EXP) ./srcs/minishell.c -o $(LEXER)

lib		: 
			@$(MAKE) -C libtools
			@$(MAKE) -C gc_memory
			
exp     : $(EXP)
		gcc $^ -o $(EXPENDER)


clean   :
		@rm -drf $(NAME) $(LEXER) $ $(PARSE) $(EXEC)

fclean : clean
			@echo "\nClean ~\n"
			@$(MAKE) -C libtools fclean
			@$(MAKE) -C gc_memory fclean