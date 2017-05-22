# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/24 14:14:44 by avenzel           #+#    #+#              #
#    Updated: 2017/05/22 13:43:53 by avenzel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME	:= $(shell uname)

NAME	= RTv1

SRC		= rtv1.c		funcs1.c	funcs2.c	ray_tracer.c	rt_funcs1.c	\
		  rt_funcs2.c	rt_funcs3.c	
OBJ		= $(SRC:.c=.o)
CC		= gcc
FLG		= -Wall -Wextra -Werror
ifeq ($(UNAME), Darwin)
ATTR	= -O3 -lmlx -lpthread -framework OpenGL -framework AppKit
endif
ifeq ($(UNAME), Linux)
ATTR	= minilibx/libmlx.a -O3 -lpthread -lX11 -lXext -lm
endif
all		: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(FLG) $(OBJ) -o $(NAME) $(ATTR)

.c.o:
	@$(CC) -c -o $@ $<

clean	: 
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all
