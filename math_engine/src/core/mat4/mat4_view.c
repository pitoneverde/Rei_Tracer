/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:24:15 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/16 17:54:00 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "utils/common.h"
#include <math.h>

// just an helper to ensure orthonormal basis and avoid gimbal lock
// fallback on -Z works because of cross product anticommutativity
static void camera_basis(t_vec3 forward, t_vec3 *right, t_vec3 *up)
{
	if (fabsf(vec3_dot(forward, VEC3_UP)) > 0.999f)
		*right = vec3_normalize(vec3_cross(VEC3_FORWARD, forward));
	else
		*right = vec3_normalize(vec3_cross(forward, VEC3_UP));
	*up = vec3_normalize(vec3_cross(*right, forward));
}

// Camera-to-world matrix (essential for RT cameras)
// eye = from, target = to, arbitrary up is y-axis
t_mat4	mat4_look_at(t_vec3 eye, t_vec3 target)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = vec3_normalize(vec3_sub(eye, target));
	camera_basis(vec3_neg(forward), &right, &up);
	return (mat4_from_basis(right, up, forward, eye));	
}

// Camera-to-world matrix (essential for RT cameras)
// Like mat4_look_at, but instead of using a point to extrapolate orientation
// just passes directly the precomputed forward orientation vector.
t_mat4	mat4_look_at_fast(t_vec3 eye, t_vec3 forward)
{
	t_vec3	right;
	t_vec3	up;
	camera_basis(vec3_neg(forward), &right, &up);
	return (mat4_from_basis(right, up, forward, eye));
}

	// return ((t_mat4) {
	// 	.mat = {
	// 		{right.x, right.y, right.z, 0},
	// 		{up.x, up.y, up.z, 0},
	// 		{forward.x, forward.y, forward.z, 0},
	// 		{eye.x, eye.y, eye.z, 1}
	// 	}
	// });