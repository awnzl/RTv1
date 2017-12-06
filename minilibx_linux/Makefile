NAME	= libmlx.a

SRC		= mlx_init.c mlx_new_window.c mlx_pixel_put.c mlx_loop.c \
	mlx_mouse_hook.c mlx_key_hook.c mlx_expose_hook.c mlx_loop_hook.c \
	mlx_int_anti_resize_win.c mlx_int_do_nothing.c \
	mlx_int_wait_first_expose.c mlx_int_get_visual.c \
	mlx_flush_event.c mlx_string_put.c \
	mlx_new_image.c mlx_get_data_addr.c \
	mlx_put_image_to_window.c mlx_get_color_value.c mlx_clear_window.c \
	mlx_xpm.c mlx_int_str_to_wordtab.c mlx_destroy_window.c \
	mlx_int_param_event.c mlx_int_set_win_event_mask.c mlx_hook.c \
	mlx_rgb.c mlx_destroy_image.c

INC		= /usr/include

OBJ		= $(SRC:.c=.o)
CC		= clang
CFLAGS	= -O3 -I$(INC)

all	: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME)	: $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean	:
	rm -rf $(OBJ) *~ core *.core

fclean	: clean
	rm -rf $(NAME)

re: fclean all
