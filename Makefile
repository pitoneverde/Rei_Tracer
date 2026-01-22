NAME=miniRT
CC=cc
CFLAGS=-Wall -Wextra -Werror -g -O0 -Iinclude -Iminilibx-linux -Ilibc/include
LDFLAGS=-lm -Lminilibx-linux -lmlx -Llibc -lft_bonus libc/libft_bonus.a

SRCS=main.c parsing.c check_ambient.c check_camera.c
HEADS=minirt.h
OBJS=$(SRCS:.c=.o)
MLX_DIR=./minilibx-linux
LIBC_DIR=./libc

all:$(NAME) $(HEADS)

$(NAME):$(OBJS)
	make -C $(LIBC_DIR) bonus
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) -c $^

mlx:
	git clone https://github.com/42paris/minilibx-linux.git

d:
	rm -rf minilibx-linux

clean:
	rm -f $(OBJS)
	make -C $(LIBC_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all mlx d clean fclean re
