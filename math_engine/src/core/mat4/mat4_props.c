/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_props.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:23:51 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 22:19:57 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

float	mat4_determinant(t_mat4 m)
{
	// TODO
	(void)m;
	return (0.0f);
}

t_mat4	mat4_inverse(t_mat4 m)
{
	// TODO
	(void)m;
	return ((t_mat4){0});
}

inline t_mat4	mat4_transpose(t_mat4 m)
{
	return ((t_mat4){
		.mat = {
			{m.m00, m.m10, m.m20, m.m30},
			{m.m01, m.m11, m.m21, m.m31},
			{m.m02, m.m12, m.m22, m.m32},
			{m.m03, m.m13, m.m23, m.m33}
		}
	});
}

// Aka sum of the diagonal elements
inline float	mat4_trace(t_mat4 m)
{
	return (m.m00 + m.m11 + m.m22 + m.m33);
}