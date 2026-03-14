/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:52:03 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/14 02:12:55 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/camera.h"
#include "utils/math_constants.h"
#include <math.h>
#include <stdlib.h>

int	camera_init(t_camera_math *cam, t_camera_data *data)
{
	float	tan_vfov_half;

	cam = malloc(sizeof(t_camera_math));
	if (!cam || !data)
		return (1);
	cam->cam_to_world = mat4_look_at_fast(data->eye, data->orientation);
	cam->near_clip = data->near;
	cam->far_clip = data->far;
	cam->image_h = data->image_h;
	cam->image_w = data->image_w;
	cam->vfov = data->vfov;
	cam->image_aspect = (float)cam->image_w / cam->image_h;
	tan_vfov_half = tanf(cam->vfov * 0.5 * DEG_TO_RAD);
	cam->canvas[2] = -tan_vfov_half;
	cam->canvas[3] = tan_vfov_half;
	cam->canvas[0] = cam->canvas[2] * cam->image_aspect;
	cam->canvas[1] = cam->canvas[3] * cam->image_aspect;
	return (0);
}