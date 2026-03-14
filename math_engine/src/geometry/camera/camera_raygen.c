/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_raygen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:51:33 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/14 02:13:39 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/camera.h"

t_ray	camera_raygen(const t_camera_math *cam, t_pixel p)
{
	(void)cam;
	(void)p;
	return (t_ray){VEC3_ZERO, VEC3_ZERO};
}