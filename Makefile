NAME=miniRT
CC=cc
CFLAGS=-Wall -Wextra -Werror -g -O2 -Iinclude -Iminilibx-linux
LDFLAGS=-lm -Lminilibx-linux/libmlx.a

SRCS=main.c
HEADS=minirt.h
OBJS=$(SRCS:.c=.o)
MLX_DIR=./minilibx-linux

all:$(NAME) $(HEADS)

$(NAME):$(OBJS)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $^

$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) -c $^

mlx:
	git clone https://github.com/42paris/minilibx-linux.git

d:
	rm -rf minilibx-linux

clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all mlx d clean fclean re