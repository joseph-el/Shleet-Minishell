# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 09:13:22 by yoel-idr          #+#    #+#              #
#    Updated: 2023/02/12 12:31:37 by aelkhali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= libtools_bonus.a

SRC 	:=	ft_strcmp_bonus.c ft_isdigit_bonus.c ft_isalnum_bonus.c ft_isalpha_bonus.c ft_isspace_bonus.c ft_strlen_bonus.c ft_memset_bonus.c ft_memmove_bonus.c ft_strlcpy_bonus.c ft_strndup_bonus.c ft_split_bonus.c\
			ft_strchr_bonus.c ft_strncmp_bonus.c ft_memcmp_bonus.c ft_memcpy_bonus.c ft_strdup_bonus.c ft_atoi_bonus.c ft_substr_bonus.c ft_strjoin_bonus.c  ft_itoa_bonus.c ft_putstr_fd_bonus.c \

FLAG 	:= -Wall -Wextra -Werror
AR 		:= ar -rc
OBJ  	:= $(SRC:.c=.o)
RESET  	:= \033[0m

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
COM_STRING   = "Compiling"

all : $(NAME)

$(NAME) : $(OBJ)
		@$(AR) $(NAME) $(OBJ)
.c.o:
		@printf "%-100.900b\r" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@)$(NO_COLOR)\n";
		@cc $(FLAG) -c $< -o $@	

clean :
		@$(RM) $(OBJ)
		
fclean : clean
		@$(RM) $(NAME)

re 	   : fclean all

.PHONY := all clean fclean re