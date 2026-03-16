#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

#include "minirt_data.h"
#include "math_engine.h"

#define IMG_WIDTH 1368
#define IMG_HEIGHT 786

#ifndef T_PIXEL_DEFINED
# define T_PIXEL_DEFINED

typedef struct s_pixel
{
	int	x;
	int y;
}	t_pixel;

#endif

t_rgb	ray_cast(t_ray ray);

#endif