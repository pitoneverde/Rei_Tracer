#ifndef MINIRT_H
# define MINIRT_H 1

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include "libft.h"
// Error: message
#define PRINT_ERR(fmt, ...) \
	do {\
		fprintf(stderr, "Error\n @ %s:%d in %s() " fmt "\n", \
		 __FILE__, __LINE__, __func__, ##__VA_ARGS__);\
	} while(0);

// to move into parser.h when split files
#include "minirt_data.h"
void    parse_input(int argc, char **argv, t_element *data_file);
bool	check_camera(char *str);
int	check_matrix_data_is_good(char **matrix);
bool convertable_double(double *value, const char *str);
bool	check_coordinates(char *s);
int	check_ambient(char *str);
int	ft_word_count(char *str);
int	check_rgb_format(char *str);
double convert_double_strtod(char *str);
int parse_double(char *str);
int	check_ambient(char *str);

#endif