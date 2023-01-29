# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 17:26:48 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/29 17:27:02 by yoel-idr         ###   ########.fr        #
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
EXP			:= ./srcs/expander/wildcard.c ./srcs/expander/expander.c ./srcs/expander/expansion.c ./srcs/expander/expander_tools.c   ./srcs/expander/expander_list.c
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