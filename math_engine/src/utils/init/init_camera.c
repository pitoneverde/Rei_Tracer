/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:34:18 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/17 00:01:05 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils/interop.h"
#include "geometry/camera.h"

// HARDCODED
int init_camera(t_element c, t_camera_math **out)
{
	(void)c;
	t_camera camera = {
		.fov = 90,
		.viewpoint = {.x = -50.0f, .y = 0.0f, .z = 20.0f},
		.orientation = {.x = 1.0f, .y = 0.0f, .z = 0.0f}
	};
	t_camera_data *camera_data = convert_camera(&camera);
	if (!camera_data)
		return (1);
	t_camera_math *cam = malloc(sizeof(t_camera_math));
	if (!cam)
	{
		free(camera_data);
		return (1);
	}
	if (camera_init(cam, camera_data))
		return (1);
	*out = cam;
	free(camera_data);
	return (0);
}