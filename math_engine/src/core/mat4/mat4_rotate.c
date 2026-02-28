/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:23:58 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/28 17:59:45 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "math.h"

// Create matrices for rotations (Tait-Bryan, aka yaw, pitch, roll)

inline t_mat4	mat4_rotation_x(float angle)
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

inline t_mat4	mat4_rotation_y(float angle)
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

inline t_mat4	mat4_rotation_z(float angle)
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

// uses Rodrigues' formula directly (could be simpler with unit quaternions)
// R = I + sinθK + (1 − cosθ)K²
t_mat4	mat4_rotation_axis(t_vec3 axis, float angle)
{
	float	c;
	float	s;
	float	t;
	t_mat4	rot;

	if (!vec3_is_normalized(axis))
		return (mat4_identity());
	c = cosf(angle);
	s = sinf(angle);
	t = 1.0f - c;
	rot = mat4_identity();
	rot.m00 = t * axis.x * axis.x + c;
	rot.m01 = t * axis.x * axis.y + s * axis.z;
	rot.m02 = t * axis.x * axis.z - s * axis.y;
	rot.m10 = t * axis.x * axis.y - s * axis.z;
	rot.m11 = t * axis.y * axis.y + c;
	rot.m12 = t * axis.y * axis.z + s * axis.x;
	rot.m20 = t * axis.x * axis.z + s * axis.y;
	rot.m21 = t * axis.y * axis.z - s * axis.x;
	rot.m22 = t * axis.z * axis.z + c;
	return (rot);
}
