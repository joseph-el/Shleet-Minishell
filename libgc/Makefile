# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/14 16:03:59 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/14 19:15:34 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := gc.a

FLAGS := -Wall -Wextra -Werror

SRCS  := ./src/gc.c

OBJS  := $(SRCS:.c=.o)

all : $(NAME)
	@echo "libgc"

$(NAME) : $(OBJS)
	@ar -rc $@ $^
	
.c.o :
		@cc $(FLAGS) -c $< -o $@

clean :
		@rm -drf $(OBJS)
	
fclean : clean
		@rm -drf $(NAME)

re : fclean all