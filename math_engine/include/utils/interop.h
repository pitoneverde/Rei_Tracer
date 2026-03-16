#ifndef INIT_H
#define INIT_H

#include "../../../include/minirt_data.h"
#include "geometry/camera.h"

#ifndef IMG_WIDTH
# define IMG_WIDTH 1368
#endif

#ifndef IMG_HEIGHT
# define IMG_HEIGHT 786
#endif

int init_math(t_element *file_data);

// ===== HELPERS =====

int init_camera(t_element c, t_camera_math **out);
int init_ambient_light(t_element a);
int init_light(t_element l);
int init_cylinder(t_element cy);
int init_plane(t_element pl);
int init_sphere(t_element sp);

// t_lighting_data	*convert_ambient_lighting(t_ambient_lighting *al);
t_camera_data	*convert_camera(t_camera *cam);
// t_cylinder_data	*convert_cylinder(t_cylinder *cy);
// t_light_data	*convert_light(t_light *l);
// t_plane_data	*convert_plane(t_plane *p);
// t_sphere_data	*convert_sphere(t_sphere *sp);


// int destroy_math(t_element *file_data);

// // ===== HELPERS =====

// int destroy_camera(t_element c);
// int destroy_ambient_light(t_element a);
// int destroy_light(t_element l);
// int destroy_cylinder(t_element cy);
// int destroy_plane(t_element pl);
// int destroy_sphere(t_element sp);

#endif