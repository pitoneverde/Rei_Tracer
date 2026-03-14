#ifndef CAMERA_H
# define CAMERA_H

# include "core/mat4.h"
# include "geometry/ray.h"

// canvas is left, right, bottom, top
typedef struct s_camera_math
{
	t_mat4	cam_to_world;

	float	near_clip;
	float	far_clip;
	int		image_h;
	int		image_w;
	float	hfov;
	
	float	canvas[4];
	float	image_aspect;
}	t_camera_math;

// ^
// optional, needed if matching real footage
// float	film_aperture_h;
// float	film_aperture_w;
// bool	fit_resolution_gate;
// float	focal_length;
// float	film_aspect;

typedef struct s_camera_data
{
	t_vec3	orientation;
	t_vec3	eye;
	float	near;
	float	far;
	int		image_h;
	int		image_w;
	float	hfov;
}	t_camera_data;

#ifndef T_PIXEL_DEFINED
# define T_PIXEL_DEFINED

typedef struct s_pixel
{
	int	x;
	int y;
}	t_pixel;

#endif

int		camera_init(t_camera_math *cam, t_camera_data *data);
t_ray	camera_raygen(const t_camera_math *cam, t_pixel p);
t_vec3	camera_eye(const t_camera_math *cam);

#endif