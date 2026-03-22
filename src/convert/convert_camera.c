/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 01:56:36 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:04:07 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

static t_camera_data	convert_camera(const t_camera *cam)
{
	t_camera_data	cam_data;

	cam_data.hfov = cam->fov;
	cam_data.eye = cam->viewpoint;
	cam_data.orientation = cam->orientation;
	cam_data.near = 1.0f;
	cam_data.far = 1000.0f;
	cam_data.image_h = IMG_HEIGHT;
	cam_data.image_w = IMG_WIDTH;
	return (cam_data);
}

int	create_camera(t_camera_math *math, t_camera *cam)
{
	t_camera_data	camera_data;

	if (!math)
		return (1);
	camera_data = convert_camera(cam);
	if (camera_init(math, camera_data))
		return (1);
	return (0);
}
