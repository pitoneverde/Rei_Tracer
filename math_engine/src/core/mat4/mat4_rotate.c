/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:23:58 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 22:19:45 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "math.h"

// Create matrices for rotations (Tait-Bryan, aka yaw, pitch, roll)

t_mat4	mat4_rotation_x(float angle)
{
	return ((t_mat4){
		.mat = {
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, cosf(angle), sinf(angle), 0.0f},
			{0.0f, -sinf(angle), cosf(angle), 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		}
	});
}

t_mat4	mat4_rotation_y(float angle)
{
	return ((t_mat4){
		.mat = {
			{cosf(angle), 0.0f, -sinf(angle), 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{sinf(angle), 0.0f, cosf(angle), 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		}
	});
}

t_mat4	mat4_rotation_z(float angle)
{
	return ((t_mat4){
		.mat = {
			{cosf(angle), sinf(angle), 0.0f, 0.0f},
			{-sinf(angle), cosf(angle), 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		}
	});
}

t_mat4	mat4_rotation_axis(t_vec3 axis, float angle)
{
	// TODO
	(void)axis;
	(void)angle;
	return ((t_mat4){0});
}
