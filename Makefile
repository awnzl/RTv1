# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/24 14:14:44 by avenzel           #+#    #+#              #
#    Updated: 2017/12/06 14:16:48 by avenzel          ###   ########.fr        #
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
ATTR	= -O3 -L ./minilibx_macos/ -lmlx -lpthread -framework OpenGL -framework AppKit
MLX_INC	= -I ./minilibx_macos/
endif
ifeq ($(UNAME), Linux)
ATTR	= -O3 -L ./minilibx_linux/ -lmlx -lpthread -lX11 -lXext -lm
MLX_INC	= -I ./minilibx_linux/
endif
all		: $(NAME)

$(NAME)	: $(OBJ) $(MLX)
	$(CC) $(FLG) $(OBJ) -o $(NAME) $(ATTR)

ifeq ($(UNAME), Darwin)
$(MLX)	:
	@make -C minilibx_macos
endif
ifeq ($(UNAME), Linux)
$(MLX)	:
	@make -C minilibx_linux
endif

.c.o:
	@$(CC) $(MLX_INC) -c -o $@ $<

clean	: 
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all
