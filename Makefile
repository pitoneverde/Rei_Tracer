NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -Iinclude -Iminilibx-linux -Ilibc/include
LDFLAGS = -lm -Lminilibx-linux -lmlx -Llibc -lft_bonus

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/check_matrix_data_is_good.c \
		$(SRC_DIR)/parsing/check_ambient.c \
		$(SRC_DIR)/parsing/check_camera.c \
		$(SRC_DIR)/parsing/check_light.c \
		$(SRC_DIR)/parsing/check_sphere.c \
		$(SRC_DIR)/parsing/check_plane.c \
		$(SRC_DIR)/parsing/parsing_utils.c \

HEADERS_DIR = include
HEADS = $(HEADERS_DIR)/minirt.h \
		$(HEADERS_DIR)/minirt_types.h \
		$(HEADERS_DIR)/minirt_data.h

OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX_DIR=./minilibx-linux
LIBC_DIR=./libc
LIBC=$(LIBC_DIR)/libft_bonus.a

all: $(NAME) $(LIBC)

$(NAME): $(OBJS) $(LIBC)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBC):
	@make -C $(LIBC_DIR) bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c  $(HEADS) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

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
	make -C $(LIBC_DIR) fclean
# 	make -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all mlx d clean fclean re
