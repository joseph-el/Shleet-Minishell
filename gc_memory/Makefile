# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 18:49:05 by yoel-idr          #+#    #+#              #
#    Updated: 2023/02/01 12:05:23 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := gc_memory.a

FLAGS := -Wall -Wextra -Werror

SRCS  := ./tools/gc_memory.c
INC   := include
OBJS  := $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rc $@ $^
	
.c.o : 
		@cc $(FLAGS) -c $< -o $@ -I $(INC)

clean :
		@rm -drf $(OBJS)
	
fclean : clean
		@rm -drf $(NAME)

re : fclean all