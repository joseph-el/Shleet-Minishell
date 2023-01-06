# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 09:13:22 by yoel-idr          #+#    #+#              #
#    Updated: 2022/10/18 19:54:34 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_1_2	 =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c\
			ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c\
			ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c\
			ft_strdup.c ft_atoi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_BON	=	$(SRC_1_2) ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c	

CC = cc
FLAG = -Wall -Wextra -Werror
AR = ar -rc
RM = rm -f
OBJ_1_2 = $(SRC_1_2:.c=.o)
OBJ_BUN = $(SRC_BON:.c=.o)

.PHONY = all clean fclean re

all : $(NAME)
	@echo "part 1 && part 2"

bonus :	$(OBJ_BUN)
		@$(AR) $(NAME) $^
		@echo "part 1 && part plus bonus part :-°"
$(NAME) : $(OBJ_1_2)
		@$(AR) $(NAME) $(OBJ_1_2)
.c.o:
		@echo compiling $< ...
		@$(CC) $(FLAG) -c $< -o $@	
clean :
		@echo "removinig all file ".o" "
		@$(RM) $(OBJ_1_2) $(OBJ_BUN)
fclean : clean
		@echo "removinig libft.a"
		@$(RM) $(NAME)
re 	   : fclean all
		@echo "update libft.a"

