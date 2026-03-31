CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3 -Iinclude -Iminilibx-linux -Ilibc/include -Imath_engine/include
LDFLAGS = -Lminilibx-linux -lmlx -Llibc -lft_bonus -Lmath_engine/build/lib -lmath_engine -lm -lX11 -lXext

NAME = miniRT

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/parsing_app.c \
		$(SRC_DIR)/parsing/parsing_app_utils.c \
		$(SRC_DIR)/parsing/check_matrix_data_is_good.c \
		$(SRC_DIR)/parsing/check_ambient.c \
		$(SRC_DIR)/parsing/check_camera.c \
		$(SRC_DIR)/parsing/check_light.c \
		$(SRC_DIR)/parsing/check_sphere.c \
		$(SRC_DIR)/parsing/check_plane.c \
		$(SRC_DIR)/parsing/check_cylinder.c \
		$(SRC_DIR)/parsing/parsing_utils.c \
		$(SRC_DIR)/parsing/parsing_utils_app.c \
		$(SRC_DIR)/parsing/init_data_minirt.c \
		$(SRC_DIR)/parsing/init_data_minirt_app.c \
		$(SRC_DIR)/parsing/ft_atod.c \
		$(SRC_DIR)/parsing/ft_strtod.c \
		$(SRC_DIR)/renderer/render.c \
		$(SRC_DIR)/renderer/ray_cast.c \
		$(SRC_DIR)/renderer/trace.c \
		$(SRC_DIR)/renderer/lighting.c \
		$(SRC_DIR)/renderer/init_math.c \
		$(SRC_DIR)/renderer/destroy_math.c \
		$(SRC_DIR)/renderer/utils.c \
		$(SRC_DIR)/convert/convert_ambient.c \
		$(SRC_DIR)/convert/convert_camera.c \
		$(SRC_DIR)/convert/convert_cylinder.c \
		$(SRC_DIR)/convert/convert_light.c \
		$(SRC_DIR)/convert/convert_plane.c \
		$(SRC_DIR)/convert/convert_sphere.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/mlx_minirt/mlx_init_windows_minirt.c\
		$(SRC_DIR)/mlx_minirt/debug_mlx_init_windows_minirt.c

HEADERS_DIR = include
HEADS = $(HEADERS_DIR)/minirt.h \
		$(HEADERS_DIR)/minirt_types.h \
		$(HEADERS_DIR)/minirt_data.h \
		$(HEADERS_DIR)/minirt_renderer.h \
		$(HEADERS_DIR)/mlx_minirt.h \
		$(HEADERS_DIR)/parsing_minirt.h \

OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX_DIR=./minilibx-linux
LIBC_DIR=./libc
LIBC=$(LIBC_DIR)/libft_bonus.a
MATH_E_DIR = ./math_engine
MATH_E = $(MATH_E_DIR)/build/lib/libmath_engine.a

all: $(NAME) $(LIBC) $(MATH_E)

$(NAME): $(OBJS) $(LIBC) $(MATH_E)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBC):
	@make -C $(LIBC_DIR) bonus

$(MATH_E):
	@make -C $(MATH_E_DIR) all

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
	make -C $(MATH_E_DIR) clean
# 	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBC_DIR) fclean
	make -C $(MATH_E_DIR) fclean

quick-test: 
	$(MAKE) -C $(MATH_E_DIR) quick-test

test:
	$(MAKE) -C $(MATH_E_DIR) test

bench:
	$(MAKE) -C $(MATH_E_DIR) bench

re: fclean all

.PHONY: all mlx d clean fclean re
