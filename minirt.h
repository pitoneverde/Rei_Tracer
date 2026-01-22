#ifndef MINIRT_H
# define MINIRT_H 1

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include "libft.h"

typedef struct s_color
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;	//unused just to pad
} t_color;

typedef union u_rgb
{
	t_color rgba;
	uint32_t hex;
} t_rgb;

typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;

typedef t_vec3 t_point3;
typedef t_vec3 t_vector3;

// Error: message
#define PRINT_ERR(fmt, ...) \
	do {\
		fprintf(stderr, "Error\n @ %s:%d in %s() " fmt "\n", \
		 __FILE__, __LINE__, __func__, ##__VA_ARGS__);\
	} while(0);

// to move into parser.h when split files
#include "minirt_data.h"
void    parse_input(int argc, char **argv, t_element *data_file);
#endif