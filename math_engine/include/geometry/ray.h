#ifndef RAY_H
#define RAY_H

#include "core/vec3.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	// float	t_max;
	// float	t_min;
}	t_ray;

t_vec3	ray_at(t_ray ray, float t);

#endif