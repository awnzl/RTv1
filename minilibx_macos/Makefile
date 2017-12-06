NAME	= libmlx.a

SRC		= mlx_shaders.c \
		mlx_new_window.m \
		mlx_init_loop.m \
		mlx_new_image.m \
		mlx_xpm.c \
		mlx_int_str_to_wordtab.c

OBJ1	= $(SRC:.c=.o)
OBJ		= $(OBJ1:.m=.o)
CC		= clang
CFLAGS	= -O3

all	: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME)	: $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean	:
	rm -rf $(OBJ) *~

fclean	: clean
	rm -rf $(NAME)
	rm -rf mlx_app

re: fclean all
