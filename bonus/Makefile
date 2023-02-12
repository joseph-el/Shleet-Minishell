# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 11:31:53 by yoel-idr          #+#    #+#              #
#    Updated: 2023/02/12 13:12:30 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 			:= minishell_bonus

FLAGS 				:= -Wall -Wextra -Werror -fsanitize=address -g
# READ_L				:= -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib -I /opt/homebrew/Cellar/readline/8.2.1/include
# 	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include	


SRCS 				:= srcs/
CC 					:= cc
RM					:= rm -f
INCLUDES			:= includes/
HEADERS 			:= environment_bonus.h executor_bonus.h expander_bonus.h lexer_bonus.h minishell_bonus.h
HEADERS 			:= $(addprefix $(INCLUDES), $(HEADERS))

RED    				:= \033[1;00m
GREEN  				:= \033[1;32m
YELLOW 				:= \033[1;33m
BLUE   				:= \033[0;34m
RESET  				:= \033[0m
COM_COLOR   		:= \033[0;34m
OBJ_COLOR   		:= \033[0;36m
OK_COLOR    		:= \033[0;32m
NO_COLOR    		:= \033[m

OK_STRING    		:= "[OK]"
COM_STRING  	    := "Compiling"
SHLEET    	 		:= "Shleet-minishell_bonus"
GARBAGE      		:= "gc_memory_bonus"
LIBT		 		:= "libtools_bonus"
DELETE       		:= "Deleting Bonus objects"


MINISHELL_FILE  	:=	minishell_bonus.c

UTILS_FILES 		:=  utils/g_error_bonus.c \
						utils/g_signel_bonus.c \
						utils/g_utils_bonus.c \
						utils/g_fd_utils_bonus.c \

LEXER_FILES 		:= 	lexer/lexer_bonus.c \
						lexer/lexer_helpful1_bonus.c \
						lexer/lexer_helpful2_bonus.c \
						lexer/list_construct_bonus.c \
						lexer/list_destroyer_bonus.c \

SYNTAX_FILES 		:=	lexer/syntax_bonus.c \

EXPANDER_FILES 		:=	expander/expander_bonus.c \
						expander/expander_helpful1_bonus.c \
						expander/expander_helpful2_bonus.c \
						expander/list_expansion_bonus.c \
						expander/list_construct_bonus.c \
						expander/wildcard_bonus.c \

EXECUTOR_FILES  	:=	executor/executor_bonus.c \
						executor/executor_utils_bonus.c \
						executor/ft_execve_bonus.c \


ENVIROMENT_FILES 	:= 	environment/environment_bonus.c \
						environment/environment_utils1_bonus.c \
						environment/environment_utils2_bonus.c \
						environment/environment_utils3_bonus.c \


BUILTINS_FILES  	:=  builtins/shleet_cd_bonus.c \
						builtins/shleet_echo_bonus.c \
						builtins/shleet_env_bonus.c \
						builtins/shleet_exit_bonus.c \
						builtins/shleet_export_bonus.c \
						builtins/shleet_pwd_bonus.c \
						builtins/shleet_unset_bonus.c \

FILES   			:= 	$(ENVIROMENT_FILES) \
						$(MINISHELL_FILE)   \
						$(EXECUTOR_FILES)   \
						$(EXPANDER_FILES)   \
						$(BUILTINS_FILES)   \
						$(SYNTAX_FILES)     \
						$(LEXER_FILES)      \
						$(UTILS_FILES)      \

FILES 				:= $(addprefix $(SRCS), $(FILES)) 
OBJS 				:= $(FILES:%.c=%.o)

GC_MEMORY_PATH		:= 	gc_memory/
LIBTOOLS_PATH		:= 	libtools/

GC_MEMORY 			:= $(addprefix $(GC_MEMORY_PATH), gc_memory_bonus.a)
LIBTOOLS 			:= $(addprefix $(LIBTOOLS_PATH), libtools_bonus.a)


all 				:	$(NAME)
							@printf "\n%b          %b" "$(GREEN) $(GARBAGE)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; 
							@printf "%b           %b" "$(GREEN) $(LIBT)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; 
							@printf "%b   %b" "$(GREEN) $(SHLEET)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; 
		
$(NAME) 			:  	$(GC_MEMORY) $(LIBTOOLS) $(OBJS)
							@$(CC) $(FLAGS) $^ -o $@ -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib
							@mv $(NAME) ../

$(LIBTOOLS)			: 	$(addprefix $(LIBTOOLS_PATH), libtools_bonus.h)
							@make -C  $(LIBTOOLS_PATH) all 

$(GC_MEMORY)    	:  	$(addprefix $(GC_MEMORY_PATH), include/gc_memory_bonus.h)
							@make -C $(GC_MEMORY_PATH) all 

.c.o		 		:	$(HEADERS)
							@printf "%-100.900b\r" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@)$(NO_COLOR)\n";
							@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDES) -I $(LIBTOOLS_PATH) -I $(addprefix $(GC_MEMORY_PATH), include) -I /opt/homebrew/Cellar/readline/8.2.1/include

clean   			:	
							@$(RM) $(OBJS)
							@make -C $(GC_MEMORY_PATH) clean
							@make -C $(LIBTOOLS_PATH) clean

fclean 				:  	clean
							@make -C $(GC_MEMORY_PATH) fclean
							@make -C $(LIBTOOLS_PATH) fclean
							@$(RM) $(NAME)

re 					: 	fclean all

.PHONY 				: 	all clean fclean re