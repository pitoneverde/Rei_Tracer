NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_strlen.c ft_isdigit.c ft_bzero.c ft_putchar.c ft_memcpy.c ft_calloc.c ft_strdup.c ft_isspec.c ft_isflag.c ft_numlen.c ft_itoa_base.c ft_unsigned_numlen.c ft_prefix.c ft_print_str.c ft_apply_padding.c ft_init_flags.c ft_itoa_hex.c ft_print_hexadecimal.c ft_print_unsigned_decimal.c ft_print_decimal_integer.c ft_print_pointer.c ft_init_format.c ft_printf.c

#SRC_B = ft_printf_bonus.c

OBJ = $(SRC:%.c=%.o)

#OBJ_B = $(SRC_B:%.c=%.o)

all:$(NAME)

$(NAME):$(OBJ)
	ar rc $(NAME) $(OBJ)

bonus: all

clean:
	rm -f $(OBJ) *~ #$(OBJ_B) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
