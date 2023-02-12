# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 17:26:48 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/30 23:47:39 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     	:= minishell
LEXER 	 	:= lexer
EXPENDER 	:= exp
PARSE    	:= parse
EXEC     	:= exec

LIB 		:= ./libtools/libtools.a ./gc_memory/gc_memory.a
UTILS 		:=   ./srcs/utils/g_error.c
EXP			:= ./srcs/expander/wildcard.c ./srcs/expander/expander.c ./srcs/expander/expansion.c ./srcs/expander/expander_tools.c   ./srcs/expander/expander_list.c
ENV         := ./srcs/environment/environment.c srcs/environment/environment_utils1.c srcs/environment/environment_utils2.c
BUILTINS    := ./srcs/builtins/shleet_cd.c ./srcs/builtins/shleet_echo.c ./srcs/builtins/shleet_env.c ./srcs/builtins/shleet_pwd.c ./srcs/builtins/shleet_unset.c ./srcs/builtins/shleet_export.c
SRC_LEXER    := ./srcs/lexer/lexer_utils.c ./srcs/lexer/lexer.c ./srcs/lexer/syntax.c ./srcs/lexer/list_destroyer.c ./srcs/lexer/list_construct.c $(ENV) $(BUILTINS)
EXC 		 := ./srcs/executor/ft_execve.c


debug 		:= -fsanitize=address -g3

all : 
	echo "minishell"
	
lexer : clean
		@echo "\nNo error\n"
		@gcc -lreadline $(UTILS) $(SRC_LEXER) $(EXC) $(LIB) $(EXP)  ./srcs/minishell.c -o $(LEXER)

dlexer : $(UTILS) $(SRC_LEXER)
		@echo "\nLexer debug\n"
		@gcc $(debug) -lreadline $(UTILS) $(SRC_LEXER) $(EXC) $(LIB) $(EXP)  ./srcs/minishell.c -o $(LEXER)

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