/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_raygen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:51:33 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/16 19:18:01 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/camera.h"

#include "utils/debug.h"
#include <stdio.h>

// px -> [-aspect, aspect]; py -> [-1, 1] in screen space
// zoom, depending on hfov, is applied when converting to camera space
t_ray	camera_raygen(const t_camera_math *cam, t_pixel p)
{
	t_ray	ray;
	float	px;
	float	py;
	t_vec3	p_world;

	// convert to screen space
	px = (2 * ((p.x + 0.5f) / cam->image_w) - 1);
	py = (1 - 2 * ((p.y * 0.5f) / cam->image_h));
	// convert to camera space
	px = px * cam->zoom * cam->image_aspect;
	py *= cam->zoom;
	p_world = mat4_transform_point(cam->cam_to_world, vec3_new(px, py, -1));
	ray.origin = camera_eye(cam);
	ray.direction = vec3_normalize(vec3_sub(p_world, ray.origin));
	ray.t_min = cam->near_clip;
	ray.t_max = cam->far_clip;

	// vec3_print("origin", ray.origin);
	// vec3_print("direction", ray.direction);
	// printf("pixel: {%d, %d}", p.x, p.y);
	// printf("point in camera space: {%7.3f, %7.3f, -1}", px, py);
	return (ray);
}