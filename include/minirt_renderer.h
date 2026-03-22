#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

#include "minirt_data.h"
#include "mlx_minirt.h"
#include "math_engine.h"

#define IMG_WIDTH 1368
#define IMG_HEIGHT 786

// #define IMG_WIDTH 400
// #define IMG_HEIGHT 300

#ifndef T_PIXEL_DEFINED
# define T_PIXEL_DEFINED

typedef struct s_pixel
{
	int	x;
	int y;
}	t_pixel;

#endif

void	render_minirt(t_mlx_minirt *mlx, t_math *math);
t_rgb	ray_cast(const t_ray ray, t_math *math);
bool	trace(const t_ray ray, const t_math *math, t_hit *near, int *idx);

t_math	*init_math(t_element *d);
void	destroy_math(t_math *math_engine);

int	create_camera(t_camera_math *math, t_camera *cam);
int create_sphere(t_sphere_math *math, t_sphere *sphere);
int create_plane(t_plane_math *math, t_plane *plane);
int create_cylinder(t_cylinder_math *math, t_cylinder *cylinder);

// int	create_ambient(t_ambient_math *math, t_ambient_lighting *al);
// t_light_data	*convert_light(t_light *l);

void	print_t_element(t_element *elem);

#endif