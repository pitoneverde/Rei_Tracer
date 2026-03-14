#ifndef RAY_H
#define RAY_H

#include "core/vec3.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	float	t_max; // should be far clip
	float	t_min; // should be near clip
}	t_ray;

t_vec3	ray_at(t_ray ray, float t);

#endif