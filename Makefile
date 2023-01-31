# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 20:20:19 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/31 21:14:25 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 			:= minishell

FLAGS 				:= -Wall -Wextra -Werror 
READ_L				:= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include
SRCS 				:= srcs/
CC 					:= cc
RM					:= rm
INCLUDES			:= includes/
HEADERS 			:= environment.h executor.h expander.h lexer.h minishell.h
HEADERS 			:= $(addprefix $(INCLUDES), $(HEADERS))

RED    				:= \033[1;31m
GREEN  				:= \033[1;32m
YELLOW 				:= \033[1;33m
BLUE   				:= \033[1;34m
RESET  				:= \033[0m

MINISHELL_FILE  	:= minishell.c

UTILS_FILES 		:=  utils/g_error.c \
					utils/g_signel.c \
					utils/g_utils.c \
					utils/print_utils.c \ #For debug

LEXER_FILES 		:=  lexer/lexer.c \
						lexer/lexer_helpful1.c \
						lexer/lexer_helpful2.c \
						lexer/list_construct.c \
						lexer/list_destroyer.c \

SYNTAX_FILES 		:=	lexer/syntax.c \

EXPANDER_FILES 		:=	expander/expander.c \
						expander/expander_helpful1.c \
						expander/expander_helpful2.c \
						expander/list_expansion.c \
						expander/list_construct.c \
						expander/wildcard.c \

EXECUTOR_FILES  	:=	executor/executor.c \
						executor/executor_utils.c \
						executor/ft_execve.c \


ENVIROMENT_FILES 	:= 	environment/environment.c \
						environment/environment_utils1.c \
						environment/environment_utils2.c \
						environment/environment_utils3.c \


BUILTINS_FILES  	:=  builtins/shleet_cd.c \
						builtins/shleet_echo.c \
						builtins/shleet_env.c \
						builtins/shleet_exit.c \
						builtins/shleet_export.c \
						builtins/shleet_pwd.c \
						builtins/shleet_unset.c \

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





all 				: $(NAME)
		
$(NAME) 			:  $(GC_MEMORY) $(LIBTOOLS) $(OBJS)
							$(CC) $(FLAGS) $^-o $@ $(READ_L)
				
$(LIBTOOLS)			 : $(addprefix $(LIBTOOLS_PATH), libtools.h)
							make -C  $(LIBTOOLS_PATH) all

$(GC_MEMORY)    	:  $(addprefix $(GC_MEMORY_PATH), include/gc_memory.h)
							make -C $(GC_MEMORY_PATH) all


.c.o		 : $(HEADERS)
					$(CC) -c $< -o $@ -I $(INCLUDE) -I $(READ_L) -I $(LIBFT_PATH) -I $(addprefix $(GC_MEMORY_PATH), include)

clean   	:	
					$(RM) $(OBJS)

fclean 		:


re 			: