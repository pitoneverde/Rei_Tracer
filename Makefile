NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -Iinclude -Iminilibx-linux -Ilibc/include
LDFLAGS = -lm -Lminilibx-linux -lmlx -Llibc -lft_bonus

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/check_ambient.c \
		$(SRC_DIR)/check_camera

HEADERS_DIR = include
HEADS = $(HEADERS_DIR)/minirt.h \
		$(HEADERS_DIR)/minirt_types.h \
		$(HEADERS_DIR)/minirt_data.h

OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX_DIR=./minilibx-linux
LIBC_DIR=./libc

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBC_DIR) bonus
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADS) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(dir $@)

mlx:
	git clone https://github.com/42paris/minilibx-linux.git

d:
	rm -rf minilibx-linux

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBC_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all mlx d clean fclean re
