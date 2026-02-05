/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:23:36 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 18:27:12 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

inline t_mat4	mat4_identity(void)
{
	return ((t_mat4){
		.mat = {
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		}
	});
}

inline t_mat4	mat4_zero(void)
{
	return ((t_mat4){
		.mat = {
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f}
		}
	});
}

// Build transformation from orientation basis and position.
// rx = right direction
// up = up direction
// fw = forward direction
// ps = position (translation)
inline t_mat4	mat4_from_basis(t_vec3 rx, t_vec3 up, t_vec3 fw, t_vec3 ps)
{
	return ((t_mat4){
		.mat = {
			{rx.x, rx.y, rx.z, 0.0f},
			{up.x, up.y, up.z, 0.0f},
			{fw.x, fw.y, fw.z, 0.0f},
			{ps.x, ps.y, ps.z, 1.0f}
		}
	});
}

inline t_mat4	mat4_from_float_array(const float arr[16])
{
	return ((t_mat4){
		.mat = {
			{arr[0], arr[1], arr[2], arr[3]},
			{arr[4], arr[5], arr[6], arr[7]},
			{arr[8], arr[9], arr[10], arr[11]},
			{arr[12], arr[13], arr[14], arr[15]},
		}
	});
}
