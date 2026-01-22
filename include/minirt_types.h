#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

#include <stdint.h>

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

#endif