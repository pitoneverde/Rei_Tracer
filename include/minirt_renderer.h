#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

#include "minirt_data.h"
#include "math_engine.h"

#define IMG_WIDTH 1366
#define IMG_HEIGHT 768

// t_lighting_data	*convert_ambient_lighting(t_ambient_lighting *al);
t_camera_data	*convert_camera(t_camera *cam);
// t_cylinder_data	*convert_cylinder(t_cylinder *cy);
// t_light_data	*convert_light(t_light *l);
// t_plane_data	*convert_plane(t_plane *p);
// t_sphere_data	*convert_sphere(t_sphere *sp);

#endif