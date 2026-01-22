#ifndef MINIRT_H
# define MINIRT_H 1

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "minirt_data.h"

// Error: message
#define PRINT_ERR(fmt, ...) \
	do {\
		fprintf(stderr, "Error\n @ %s:%d in %s() " fmt "\n", \
		 __FILE__, __LINE__, __func__, ##__VA_ARGS__);\
	} while(0);

//parser utils
int	ft_word_count(char *str);

bool	check_camera(char *str);

int check_matrix_data_is_good(char **matrix);
int parse_input(int argc, char **argv, t_element *data_file);
#endif
