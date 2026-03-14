/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_eye.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:48:58 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/14 01:51:27 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/camera.h"

t_vec3	camera_eye(const t_camera_math *cam)
{
	t_vec3 eye;

	eye.x = cam->cam_to_world.m30;
	eye.y = cam->cam_to_world.m31;
	eye.z = cam->cam_to_world.m32;
	return (eye);
}