/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:52:03 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/16 18:50:14 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/camera.h"
#include "utils/math_constants.h"
#include <math.h>
#include <stdlib.h>

#include "utils/debug.h"

// camera initialization
// conventions: hfov is horizontal fov per subject (in degrees)
// canvas is symmetrical across the center (0, 0)
// top = ((r - l)/aspect)/2 = 2r/aspect/2 = r/aspect
int	camera_init(t_camera_math *cam, t_camera_data *data)
{
	if (!cam || !data)
		return (1);
	cam->cam_to_world = mat4_look_at_fast(data->eye, data->orientation);
	mat4_print("internal cam matrix", cam->cam_to_world);
	cam->near_clip = data->near;
	cam->far_clip = data->far;
	cam->image_h = data->image_h;
	cam->image_w = data->image_w;
	cam->hfov = data->hfov;
	cam->image_aspect = (float)cam->image_w / cam->image_h;
	cam->zoom = tanf(cam->hfov * 0.5 * DEG_TO_RAD);
	cam->canvas[1] = cam->zoom * cam->near_clip;
	cam->canvas[0] = -cam->canvas[1];
	cam->canvas[3] = (cam->canvas[1] / cam->image_aspect);
	cam->canvas[2] = -cam->canvas[3];
	return (0);
}