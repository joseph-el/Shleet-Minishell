# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 09:13:22 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/17 00:10:51 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= libtools.a

SRC 	:=	ft_isdigit.c ft_isalnum.c ft_isspace.c ft_strlen.c ft_memset.c ft_memmove.c ft_strlcpy.c ft_strndup.c \
			ft_strchr.c ft_strncmp.c  ft_memcmp.c ft_memcpy.c ft_strdup.c ft_atoi.c ft_substr.c ft_strjoin.c  ft_itoa.c ft_putstr_fd.c \

FLAG 	:= -Wall -Wextra -Werror
AR 		:= ar -rc
OBJ  	:= $(SRC:.c=.o)

all : $(NAME)
	@echo "\nlibtools\n"

$(NAME) : $(OBJ)
		@$(AR) $(NAME) $(OBJ)
.c.o:
		@cc $(FLAG) -c $< -o $@	
clean :
		@$(RM) $(OBJ)
		
fclean : clean
		@$(RM) $(NAME)

re 	   : fclean all

.PHONY := all clean fclean re