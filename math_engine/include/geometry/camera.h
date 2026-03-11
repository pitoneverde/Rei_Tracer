#ifndef CAMERA_H
# define CAMERA_H

# include "core/mat4.h"

typedef struct s_camera
{
	t_mat4	cam_to_world;

	float	near_clip;
	float	far_clip;
	int		image_h;
	int		image_w;
	float	vfov;
	
	float	canvas[4];
	float	image_aspect;
}	t_camera;
// ^
// optional, needed if matching real footage
// float	film_aperture_h;
// float	film_aperture_w;
// bool	fit_resolution_gate;
// float	focal_length;
// float	film_aspect;

int camera_init();

#endif