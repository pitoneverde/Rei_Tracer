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

t_math	*init_math(t_element *d);
void	destroy_math(t_math *math_engine);

// t_lighting_data	*convert_ambient_lighting(t_ambient_lighting *al);
// int	create_ambient(t_ambient_math *math, t_ambient_lighting *al);
int	create_camera(t_camera_math *math, t_camera *cam);
// t_cylinder_data	*convert_cylinder(t_cylinder *cy);
// t_light_data	*convert_light(t_light *l);
// t_plane_data	*convert_plane(t_plane *p);
// t_sphere_data	*convert_sphere(t_sphere *sp);
void	print_t_element(t_element *elem);


t_rgb	ray_cast(t_ray ray);

#endif