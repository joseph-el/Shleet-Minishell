# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 18:49:05 by yoel-idr          #+#    #+#              #
#    Updated: 2023/02/12 12:32:19 by aelkhali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := gc_memory_bonus.a

FLAGS := -Wall -Wextra -Werror

SRCS  := ./tools/gc_memory_bonus.c
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