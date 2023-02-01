# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 11:31:53 by yoel-idr          #+#    #+#              #
#    Updated: 2023/02/01 12:23:01 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 			:= minishell

FLAGS 				:= -Wall -Wextra -Werror 
READ_L				:= -lreadline
SRCS 				:= srcs/
CC 					:= cc
RM					:= rm -f
INCLUDES			:= includes/
HEADERS 			:= environment.h executor.h expander.h lexer.h minishell.h
HEADERS 			:= $(addprefix $(INCLUDES), $(HEADERS))

RED    				:= \033[1;00m
GREEN  				:= \033[1;32m
YELLOW 				:= \033[1;33m
BLUE   				:= \033[0;34m
RESET  				:= \033[0m

MINISHELL_FILE  	:= ./srcs/minishell.c

UTILS_FILES 		:=  ./srcs/utils/g_error.c \
						./srcs/utils/g_signel.c \
						./srcs/utils/print_utils.c \
						./srcs/utils/g_utils.c \

LEXER_FILES 		:= 	./srcs/lexer/lexer.c \
						./srcs/lexer/lexer_helpful1.c \
						./srcs/lexer/lexer_helpful2.c \
						./srcs/lexer/list_construct.c \
						./srcs/lexer/list_destroyer.c \

SYNTAX_FILES 		:=	./srcs/lexer/syntax.c \

EXPANDER_FILES 		:=	./srcs/expander/expander.c \
						./srcs/expander/expander_helpful1.c \
						./srcs/expander/expander_helpful2.c \
						./srcs/expander/list_expansion.c \
						./srcs/expander/list_construct.c \
						./srcs/expander/wildcard.c \

EXECUTOR_FILES  	:=	./srcs/executor/executor.c \
						./srcs/executor/executor_utils.c \
						./srcs/executor/ft_execve.c \


ENVIROMENT_FILES 	:= 	./srcs/environment/environment.c \
						./srcs/environment/environment_utils1.c \
						./srcs/environment/environment_utils2.c \
						./srcs/environment/environment_utils3.c \


BUILTINS_FILES  	:=  ./srcs/builtins/shleet_cd.c \
						./srcs/builtins/shleet_echo.c \
						./srcs/builtins/shleet_env.c \
						./srcs/builtins/shleet_exit.c \
						./srcs/builtins/shleet_export.c \
						./srcs/builtins/shleet_pwd.c \
						./srcs/builtins/shleet_unset.c \

FILES   			:= 	$(ENVIROMENT_FILES) \
						$(MINISHELL_FILE)   \
						$(EXECUTOR_FILES)   \
						$(EXPANDER_FILES)   \
						$(BUILTINS_FILES)   \
						$(SYNTAX_FILES)     \
						$(LEXER_FILES)      \
						$(UTILS_FILES)      \

OBJS 				:= $(FILES:%.c=%.o)

GC_MEMORY_PATH		:= 	gc_memory/
LIBTOOLS_PATH		:= 	libtools/

GC_MEMORY 			:= $(addprefix $(GC_MEMORY_PATH), gc_memory.a)
LIBTOOLS 			:= $(addprefix $(LIBTOOLS_PATH), libtools.a)

all 				:	$(NAME)
							@echo  "$(GREEN) Shleet-minishell $(RESET)" 
		
$(NAME) 			:  	$(GC_MEMORY) $(LIBTOOLS) $(OBJS)
							@$(CC) $(FLAGS) $(READ_L) $^ -o $@
				
$(LIBTOOLS)			 : 	$(addprefix $(LIBTOOLS_PATH), libtools.h)
							@make -C  $(LIBTOOLS_PATH) all 

$(GC_MEMORY)    	:  	$(addprefix $(GC_MEMORY_PATH), include/gc_memory.h)
							@make -C $(GC_MEMORY_PATH) all 

.c.o		 		:	$(HEADERS)
# echo "\033[0;33mGenerating Shleet-Minishell objects... $(RESET) $< $(RESET)" 
							@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDES) -I $(LIBTOOLS_PATH) -I $(addprefix $(GC_MEMORY_PATH), include)

clean   			:	
							@echo "$(BLUE) Deleting objects $(RESET)" 
							@$(RM) $(OBJS)
							@make -C $(GC_MEMORY_PATH) clean
							@make -C $(LIBTOOLS_PATH) clean

fclean 				:  	clean
							@echo "$(BLUE) Deleting $(RESET)" 
							@make -C $(GC_MEMORY_PATH) fclean
							@make -C $(LIBTOOLS_PATH) fclean
							@$(RM) $(NAME)

re 					: 	fclean all

.PHONY 				: 	all clean fclean re