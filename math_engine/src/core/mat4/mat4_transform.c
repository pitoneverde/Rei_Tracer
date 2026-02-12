/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:24:06 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 22:46:04 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

// Transform point (w=1, includes translation)
t_vec3	mat4_transform_point(t_mat4 m, t_vec3 p)
{
	return ((t_vec3){
		p.x * m.m00 + p.y * m.m10 + p.z * m.m20 + m.m30,
		p.x * m.m01 + p.y * m.m11 + p.z * m.m21 + m.m31,
		p.x * m.m02 + p.y * m.m12 + p.z * m.m22 + m.m32
	});
}

// Transform vector (w=0, excludes translation - for directions)
t_vec3	mat4_transform_vector(t_mat4 m, t_vec3 v)
{
	return ((t_vec3){
		v.x * m.m00 + v.y * m.m10 + v.z * m.m20,
		v.x * m.m01 + v.y * m.m11 + v.z * m.m21,
		v.x * m.m02 + v.y * m.m12 + v.z * m.m22
	});
}

// Transform normal (inverse-transpose for non-uniform scaling)
t_vec3	mat4_transform_normal(t_mat4 m, t_vec3 n)
{
	t_mat4	t;
	// should use the upper left 3x3 inverse-transpose?

	t = mat4_transpose(mat4_inverse(m));
	return ((t_vec3){
		n.x * m.m00 + n.y * m.m10 + n.z * m.m20,
		n.x * m.m01 + n.y * m.m11 + n.z * m.m21,
		n.x * m.m02 + n.y * m.m12 + n.z * m.m22
	});
}
