/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:24:15 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/02 16:25:04 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "utils/math_constants.h"

// Camera-to-world matrix (essential for RT cameras)
// eye = from, tsrget = to, arbitrary up is y-axis
// suffers from gimbal lock: if forward is parallel to arbitrary_up,
// vec3_cross fails to yield right vector and returns 0, dividing by zero
// then yields an ill-formed matrix, with nan entries
t_mat4	mat4_look_at(t_vec3 eye, t_vec3 target, t_vec3 arbirary_up)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	forward = vec3_normalize(vec3_sub(eye, target));
	right = vec3_normalize(vec3_cross(arbirary_up, forward));
	up = vec3_cross(forward, right);
	return ((t_mat4) {
		.mat = {
			{right.x, right.y, right.z, 0},
			{up.x, up.y, up.z, 0},
			{forward.x, forward.y, forward.z, 0},
			{eye.x, eye.y, eye.z, 1}
		}
	});
}
